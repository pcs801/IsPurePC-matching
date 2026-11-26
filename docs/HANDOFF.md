# 交接：下一个会话从这里开始

## 当前进度

- 阶段：**M2.5 完成**（hard 调用类 702 + likely/unaligned 救援）
- 上一次更新：2026-11-26 23:00
- 验收：`make check` → **SHA-256 = `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147` = 原版**（其中 **223 个函数 / 5,008 字节**已改由 C 提供）
- M2.5：新写 `tools/call_gen.py`（jal/j → extern 原型 + 普通调用，忽略标准栈帧），跑 hard 的 c1+b0 / c2-3+b0 共 702 个 → **104 MATCH（14.8%）**，命中集中在单调用、≤32 字节（c1 99/338，≤32B 86/191）；likely 174 个 0 命中；unaligned 173 个现有模板 0 命中、LLM 0/172
- 下一步：**M3** — padding gate 决策（70 个 core-only medium 未进 overrides）+ hard 后续批次（c1+b0+padding 118、c2-3+b1 98）+ call_gen 栈帧对齐

---

## 你的任务（一句话）

M1–M2.4 已收口，M2.5 已完成：hard 调用类 702 个（c1+b0 / c2-3+b0）用新写的 `tools/call_gen.py` 跑出 104 命中（14.8%）；likely 174 与 unaligned 173 两组救援失败（0 命中），原因已写入 `docs/m2-5-hard-calls.md`。`make check` 仍 SHA 一致，223 个函数 / 5,008 字节来自 C。下一步 M3：先定 padding gate（70 个 core-only medium），再做 hard 的 c1+b0+padding / c2-3+b1。

---

## 1. 先读

0. `docs/m2-2-batch.md` — **M2.2 批次报告**（分档/认领/生成器/50 函数结果/诚实边界）
1. `docs/build.md` — **一条命令构建与验收**
2. `docs/m1-image.md` — reloc resolver 规则、段拼接、双验证、诚实边界
3. `docs/splat-setup.md` — splat 的 4 个坑
4. `docs/g-distribution.md` — per-TU `-G` 普查
5. `docs/STATE.json` — gate 全绿

## 2. 构建（M1 已固化）

```bash
python tools/build.py check     # splat -> asm -> resolve -> overrides -> image -> sha256
python tools/build.py check --fast   # 跳过 splat
python tools/build.py ld        # 额外：GNU ld 独立验证 .text
python tools/build.py configure # 重生成 per-TU -G 配置
python tools/build.py overrides # 只编译+校验 config/overrides.json（约 5 秒）
```

**必须看到**：`RESULT: MATCH`。耗时约 2–3 分钟。

## 3. 环境（已就绪）

```
WSL2 Ubuntu  E:\wsl\Ubuntu
/opt/ee/bin/ee-gcc 2.96-ee-001003-1     /opt/ee/ee/bin/as 2.10-ee
/opt/ee-ld/bin/mips-ps2-decompals-ld (GNU ld 2.40)   /usr/local/bin/ee-ld
Windows Python 3.10: splat 0.50.1 + spimdisasm 1.42.4
objdiff: toolchain/dl/objdiff-cli.exe
```

硬约束：汇编在 WSL 的 `/root/work`；`/mnt/e` 会让 2.96 cc1/ld 崩；`/tmp` 重启即清空。

## 4. 事实速查

| 项 | 值 |
|---|---|
| 编译器 | ee-gcc 2.96-ee-001003-1，`-O2 -mips3` |
| per-TU -G | 6 个 needs_G8 区间（覆盖 557KB），默认 -G0；见 `config/tu_g.json` |
| 函数分布 | needs_G8 727 / ambiguous 1,714 / local 1,526（候选 761 里 76/181/504） |
| gp | 0x002779F0 |
| .text 重建 | 0 差异（resolver 与 GNU ld 双证） |
| 整镜像 | SHA 一致 |
| 符号 | `config/symbol_addrs.txt` 3,966 个 |
| C 覆盖 | 5 个 local 函数 / 104 字节 / `config/overrides.json` |

## 5. 匹配循环（M2 起点）

1. 从 `asm/1000.s` 或 `disasm_text.txt` 取函数
2. 查 `config/build_config.json` 的 `g_map` 决定 `-G0`/`-G8`
3. 写 C（`// FUNCTION: SLPM <addr>`，函数名 `FUN_<addr>` 对齐 splat）
4. 在 `config/overrides.json` 登记 `{addr,size,source,g,status:"todo"}`，`make overrides` 编译+逐字节比对（重定位感知）
5. 不中先查：**常量vs符号地址 / 返回类型 / store 顺序 / 是否有 reload（volatile 类）**
6. 命中后把 status 改成 `matched`，`make check` 确认 SHA 仍一致，记 `progress/ledger.tsv`

## 6. M2 清单

1. ✅ `tools/triage.py`：size/叶函数/分支/FPU/padding/gp → easy 139 / medium 195 / hard 3,632
2. ✅ `build/queue.json` + `tools/claims.py`（原子认领 + 租约，本地版 rac4 思路）
3. ✅ `tools/match_kit.py`：批量编译 + 重定位感知逐字节比对；objdiff-cli 还没接
4. ✅ `auto_match.py` 命中时自动追加 `progress/ledger.tsv`
5. ✅ easy 139 全部跑完：107 MATCH（77.0%），25 MISS，7 UNSUPPORTED
6. ✅ `tools/llm_match.py`：证据卡 + LLM + 判定循环；medium 195 → 44 LLM + 33 baseline = **77（39.5%）**
7. ✅ `tools/branch_gen.py`：if/else + switch/if-链 + 循环 + likely 模板；分支类累计 17/72
8. ✅ `tools/hard_classes.py` → `build/hard-classes.json`：hard 3,632 个四维分类
9. 🟡 深度 thinking 模式：网关忽略 budget_tokens，长 prompt 随机挂起；只拿到 7 个有效样本（0 命中）
10. ✅ `tools/call_gen.py`：jal/j → extern 原型 + 普通调用（忽略标准栈帧）；hard 702 个调用类 → **104 命中（14.8%）**
11. ❌ likely 174：branch_gen 加 likely 模板后仍 0 命中（硬件轮询/多返回点）
12. ❌ unaligned 173：现有模板 3 个有候选、0 命中；LLM 0/172

## 7. 判据（M2）

| 结果 | 动作 |
|---|---|
| 无人值守跑完 50 函数 | 进 M3 批量 |
| 匹配率 <50% | 检查 objdiff 工程配置与符号名对齐 |

## 8. 回写（必须做）

1. `docs/STATE.json`（phase、next_action、gates、notes）
2. 本文件顶部「当前进度」
3. 新匹配函数进 `src/` + `progress/ledger.tsv`
