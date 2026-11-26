# M2.6 决策：全面转逐函数 LLM worker（全量，不试点）

> 日期：2026-11-26。用户决定：不做 50 个试点，直接全量转逐函数 worker。

## 队列

- 范围：剩余 **3,743** 个未匹配函数（3,966 - 223）
- 排序：按 `build/hard-classes.json` 的工作类别，**先易后难**
  1. 无分支、调用 ≤1、size ≤64
  2. 分支 ≤3、调用 ≤3、size ≤128
  3. 其余
  4. 特殊指令（likely/unaligned/FPU/syscall）放最后
- 排除：SDK 库函数（not-ours）、编译器内置

## 批处理

- 批大小：**80 个/批**（预算充足，提高并行度）
- 每批结束：写 `build/m26-batch-N.json`（命中/未命中/token）、更新 ledger、跑 `make progress`
- 批间不等待人工确认（全量连续跑）

## 三个保险（必须实现）

1. **命中率门禁**：连续 **3 批**命中率 <10% → 自动暂停，写 `docs/m2-6-stall.md` 并停
2. **token 上限**：每批 token 上限 **100M**（80 函数 × 1.25M），总预算 **5.0B**
3. **失败归档**：单函数重试 ≤**60** 次，仍失败 → `known-hard`，不阻塞队列

## 预算预期

- 用户已确认：**3.0B 可接受，5.0B 也可以**，预算不是约束
- 3,743 × 0.5M ≈ 1.9B（乐观）；× 0.8M ≈ 3.0B（悲观）；按 5.0B 上限跑
- 预算放开的代价：门禁必须真实生效，否则无效尝试会烧掉全部额度

## 停止条件（任一）

1. 队列跑完
2. 命中率门禁触发
3. token 预算耗尽
4. 用户叫停



---

## 修订（2026-11-26 23:45）：写 C 交给 agent，脚本只做调度与判定

原方案用脚本调 API 生成 C，证据卡缺类型、无法自省、思考受限。改为：

### 分工

| 层 | 谁做 | 内容 |
|---|---|---|
| 调度 | 脚本 | 队列、认领、沙箱、编译、match_kit 判定、记账、进度 |
| 写 C | **agent（subagent / AgentTeams 成员）** | 读证据卡、翻旧项目、写 C、看 diff、自己改、循环到 MATCH 或 60 次止损 |

### 证据卡（每次派给 agent）

1. 目标函数完整反汇编 + 原始字节
2. `config/types.json`（161 个结构体、716 个字段，来自旧项目 `IsPurePC/include/ispure/`）
3. 同形态已匹配函数的源码（从 `src/functions/` 取 3 个）
4. 上轮 diff 的具体指令（寄存器/指令名，不是 diff_words 数字）
5. ABI 与允许的 `-G`

### 已完成的准备

- `tools/export_types.py` → `config/types.json`（161 structs / 716 fields）

### 队列不变

3,743 个，先易后难，批 80，三个保险不变。



---

## 修订二（2026-11-26 23:50）：按当前 harness 适配，不照抄 Claude Code

### 事实

- 当前环境只有 **opencode-go / deepseek-v4.1-flash** 一个模型（`list_subagent_models` 实测）。
- 没有 Claude、没有 tier 升级、没有 Codex。
- DSH 独有能力：**run_code 程序化批量调用工具**（一个程序内循环编译/判定/记账）、subagent、AgentTeams、schedule。

### 结论

不能照抄“一函数一 Claude Code 会话”的形态。适配为：

```
run_code 程序（主流水线，确定性）
  1. 读队列，取 20 个函数
  2. 生成证据卡（反汇编 + config/types.json + 同形态源码 + ABI）
  3. 一次 subagent 调用，要求它输出 20 个 C（JSON）
  4. 批量编译（一次 WSL 调用）
  5. match_kit 批量判定
  6. 失败者生成“指令级 diff”卡，进入下一轮（最多 3 轮）
  7. 记账 + make progress
```

- 批次：**20 个/批**（不是 80；flash 模型单次输出上限更低）
- 每批一个 subagent，不是每函数一个
- subagent 用同一个模型（没有更强可选），靠“证据卡质量 + 多轮 diff”提升，不靠换模型
- 确定性工作（编译/判定/diff/记账）全部在 run_code 里批量做，不消耗 LLM

### 证据卡内容（每函数）

1. 反汇编全文 + 原始字节
2. `config/types.json` 中相关结构体（按字段偏移匹配）
3. `src/functions/` 中同形态已匹配源码 3 个
4. 上一轮的具体指令差异（如 `sll` vs `sra`，`v0` vs `a0`）
5. 允许的 `-G`

### 与 Claude Code 版的差异

| 项 | Claude Code 版 | 本适配 |
|---|---|---|
| 模型 | Claude Opus/Sonnet/Haiku 分层 | 单一 DeepSeek V4.1 Flash |
| 粒度 | 一函数一会话 | **一批 20 函数一次调用** |
| 确定性工作 | agent 自己跑命令 | **run_code 批量做** |
| 升级路径 | 换模型（tier） | 无；只能改证据卡/多轮 |
| 成本 | 每函数 0.3–0.8M | 目标每函数 ≤0.2M（批量摊薄） |

## 产出

- `tools/worker_match.py`：一函数一沙箱，证据卡 → LLM → 编译 → 匹配 → 重试
- `build/m26-queue.json`：3,743 个函数的有序队列
- `docs/m2-6-worker.md`：最终统计（命中率、token、known-hard 清单）
