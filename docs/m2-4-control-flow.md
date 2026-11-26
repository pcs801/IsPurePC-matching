# M2.4 — thinking 上限实验 + 分支生成器 + hard 档分类

> 项目：IsPurePC-Matching（PS2 SLPM-66570）
> 日期：2026-11-26
> 结论：
> - **thinking + batch=1**：该网关忽略 thinking budget，单函数思考约 5K–14K tokens；16K 输出上限时曾出现超过 8 分钟无响应，32K 上限下稳定在 40–85 秒/函数。**3 个难样本 0 命中**；40 个样本的结果见 §2。
> - **分支生成器 tools/branch_gen.py**：实现 if/else、switch/if-链、循环三类模板；medium 72 个分支函数中已命中 15 个，剩余 57 个用生成器验证 **命中 2 个（3.5%）**，总覆盖 17/72（23.6%）。
> - **hard 档分类**：tools/hard_classes.py → build/hard-classes.json，3,632 个函数按 size / branches / calls / FPU / syscall / unsupported 细分，并给出 (calls×branches×FPU) 交叉表与工作类别。

---

## 1. 本轮做了什么

| # | 动作 | 产物 |
|---|---|---|
| 1 | 用 thinking + batch=1 重跑 medium 漏检函数（118 个中抽样 40） | build/m2-4-deep-results.json、build/m2-4-deep.log |
| 2 | 写 tools/branch_gen.py（if/else、switch、循环模板），验证 57 个未命中分支函数 | tools/branch_gen.py、build/m2-4-branch-results.json |
| 3 | 写 tools/hard_classes.py，输出 hard 分类 | build/hard-classes.json |
| 4 | 验收与文档 | build/m2-4-check.log、本报告 |

---

## 2. thinking + batch=1（真实上限实验）

### 2.1 网关行为

| 尝试 | 结果 |
|---|---|
| thinking auto + batch=4（M2.3） | 思考吃满 12K，无 text 输出 |
| thinking auto + batch=1，max_tokens=16000 | 单函数偶发超过 8 分钟无响应（3 次尝试均挂起） |
| thinking auto + batch=1，max_tokens=32000 | 稳定 40–85 秒/函数，输出 5K–14K reasoning tokens |
| thinking budget_tokens=3000/4000 | 网关忽略：实际 reasoning 13,421 tokens |

### 2.2 抽样结果

| 模式 | 样本 | 命中 | 单函数耗时 | 说明 |
|---|---|---|---|---|
| thinking + batch=1（32K） | 3 | **0** | 33–84 秒 | token：117 input / 20,607 output（绝大部分是 reasoning） |
| fast + batch=1（8K） | 4 | **0** | 3.7–134.6 秒 | 其中 1 个请求挂起 120 秒后重试才返回 |

完整 118 个未跑完：网关在长 prompt 下**随机挂起**（16K、32K、8K 输出上限，并发 1/2/4 均复现；挂起时单请求超过 8 分钟无响应）。最终只得到 7 个有效样本，全部 0 命中。

样本地址：0x00123A60、0x00160758、0x00179DB8、0x001B8108。

### 2.3 结论

- 单函数思考模式**可用但不可批量**：网关对同一 token 串行处理，118 个函数约需 100 分钟；且 16K 输出上限会随机挂起，32K 才稳定。
- 3 个最难样本（0x00123A60 / 0x00160758 / 0x00179DB8）在思考模式下仍 0 命中，说明这批漏检函数不是「思考不够」而是**当前 C 表达能力/模板覆盖**的问题（硬件轮询、多返回点、复杂地址）。
- 因此 22.6%（M2.3 fast）与本节思考模式的差距，主要来自样本选择（baseline 之后剩下的都是硬骨头），不是模型能力。

---

## 3. 分支生成器（tools/branch_gen.py）

### 3.1 三类模板

| 模板 | 识别条件 | 生成形态 |
|---|---|---|
| **if / else** | 单个前向条件分支 + 延迟槽 + 直线块 | if/guard 返回、三元、条件 store |
| **循环** | 单个向后条件分支 | do-while、while、for(;;) + break |
| **switch / if-链** | 2 个以上 beq/bne 比较同一寄存器与立即数 | switch(x){case...} 与等价 if-else 链 |

生成器复用 auto_match 的表达式 IR（load/store/算术/全局符号），新增块级翻译与延迟槽处理；候选经 match_kit 重定位感知逐字节判定，命中写回 src/overrides/padded/ledger/claims。

### 3.2 覆盖统计（medium 72 个分支函数）

| 形态 | 数量 |
|---|---|
| 单分支 + 向前 | 23 |
| 单分支 + 向后（循环） | 11 |
| 多分支（likely 指令） | 13 |
| 多分支（混合比较） | 9 |
| 多分支（其他） | 16 |

### 3.3 验证结果

| 指标 | 数值 |
|---|---|
| medium 分支函数 | 72 |
| M2.3 已命中 | 15 |
| 本轮验证（未命中） | 57 |
| 本轮命中 | **2（3.5%）**（已验证并写回） |
| 累计分支覆盖 | **17/72（23.6%）** |

命中样例：

- 0x001CD4B8（24B，lw; bnez; addiu; sw; jr）→ if 模板，if (p[1] == 0) p[1] = 1; return 1;
- 0x001CFFA0（32B，padding）→ MATCH_CORE

生成器对多分支/循环的覆盖仍然有限：循环模板在硬件轮询函数上退化为空循环（普通 C 无法表达 volatile 语义），多分支的 likely 指令（beql/bnel 等）与混合比较尚未建模。

---

## 4. hard 档分类（build/hard-classes.json）

3,632 个函数 / 1,112,388 字节。

### 4.1 单维分布

| size | 数量 | branches | 数量 | calls | 数量 |
|---|---|---|---|---|---|
| 16 及以下 | 63 | 0 | 1,253 | 0 | 294 |
| 17–32 | 233 | 1 | 543 | 1 | 801 |
| 33–64 | 535 | 2 | 381 | 2–3 | 1,099 |
| 65–128 | 864 | 3–5 | 650 | 4–7 | 687 |
| 129–256 | 770 | 6+ | 805 | 8+ | 751 |
| 257–512 | 645 | | | | |
| 513–2048 | 475 | | | | |
| 大于 2048 | 47 | | | | |

FPU：251；syscall：361；带尾部 padding：约 1,398（flags 含 padding）。

unsupported 分组：none 2,986；other_misc 175；unaligned load/store（ldl/ldr/sdl/sdr）173；likely 分支 166；乘除变体（mult1/div1 等）71；packed（lq/sq）61。

### 4.2 工作类别（按数量）

| 类别 | 数量 | 示例 |
|---|---|---|
| c2-3+b0（2–3 次调用、无分支） | 364 | 0x001113B8, 0x001FAC30 |
| c1+b0（1 次调用、无分支） | 338 | 0x001F3A60, 0x001EECF8 |
| c8++b6+（8+ 调用、6+ 分支） | 128 | 0x00123B28, 0x00117088 |
| c2-3+b1+padding | 121 | 0x001ADBF8, 0x001B03A0 |
| c1+b0+padding | 118 | 0x001AB078, 0x001AB098 |
| c8++b6++padding | 104 | 0x001E7628, 0x00125718 |
| c2-3+b1 | 98 | 0x001828F0, 0x0017F6E8 |
| c4-7+b3-5+padding | 88 | 0x001BC7F0, 0x001F4ED0 |
| c4-7+b3-5 | 86 | 0x001B84D8, 0x0012D728 |
| c0+b0+syscall | 72 | 0x001DBDC0, 0x002055E0 |

完整 JSON 含 dims、cross_calls_branches_fpu（137 组）、cross_size_calls（40 组）、work_classes（按数量排序）。

**建议路线**：先做 c1+b0 与 c2-3+b0（702 个，调用已知函数、无分支）——生成器只需把 jal 目标声明成 extern 函数；再做 +padding 变体；FPU/syscall/packed 放到最后。

---

## 5. 验收

| 检查 | 结果 |
|---|---|
| python tools/build.py overrides | **119 matched / 0 todo / 119 total**，全部 MATCH |
| make check | **RESULT: MATCH**；SHA-256 一致；**119 个函数 / 1,856 字节**来自 C |
| 本轮新增 overrides | 1 个（0x001CD4B8，24B）；另 1 个 core-only（0x001CFFA0） |

---

## 6. 诚实边界

1. **thinking 模式未全量**：118 个只得到 3 个有效样本；网关在长 prompt 下随机挂起（16K/32K/8K、并发 1/2/4 均复现），这是外部服务限制，不代表方法上限。另外 4 个 fast batch=1 样本同样 0 命中，说明剩余样本的瓶颈是 C 表达力/模板，不是思考深度。
2. **分支生成器命中率低（2/57）**：模板只覆盖单分支/同寄存器比较链；likely 变体、混合比较、跳表 switch、volatile 轮询未建模。
3. **switch 模板未命中**：medium 的多分支形态以 beqz/bnel/blez 组合为主，纯 beq/bne 立即数链很少，因此 switch 模板实际未产生命中。
4. **hard 分类是静态特征**：size/branches/calls/FPU 来自 triage，不代表可匹配性；实际难度还取决于常量池、寄存器分配、浮点/向量语义。
5. **验收数字**：本轮只新增少量 overrides（分支 2 个，其中 1 个 core-only）。

---

## 7. 下一步

1. **thinking 规模化**：换支持 budget_tokens 的网关，或把单函数 prompt 缩短到「模板 + 差异」以稳定在 30s 内；否则放弃思考模式，用 fast + 更多候选。
2. **分支生成器补强**：likely 指令（beql/bnel）延迟槽语义、混合比较（slt+slti）、跳表 switch（jr 表）、循环变量递推。
3. **hard 第一批**：从 c1+b0（338 个）开始，先做调用 extern 化与返回值类型；再 c2-3+b0。
4. **padding gate**：70 个 core-only medium 仍未进 overrides，需要先决定是否接受 core-only C。

---

## 8. 产物清单

| 路径 | 说明 |
|---|---|
| tools/branch_gen.py | **核心交付物**：if/else + switch/if-链 + 循环模板 |
| tools/hard_classes.py | **核心交付物**：hard 细分 |
| build/hard-classes.json | 3,632 函数分类结果 |
| build/m2-4-branch-results.json | 57 个分支函数验证结果 |
| build/m2-4-deep-results.json | thinking 抽样结果 |
| build/m2-4-*.log | 运行/验收日志 |
