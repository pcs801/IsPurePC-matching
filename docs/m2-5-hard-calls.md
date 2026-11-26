# M2.5 — hard 调用类 702 + likely / unaligned 救援

> 项目：IsPurePC-Matching（PS2 SLPM-66570）
> 日期：2026-11-26
> 结论：
> - **hard c1+b0 / c2-3+b0 共 702 个**：新写 tools/call_gen.py（jal/j → extern 原型 + 普通调用，忽略标准栈帧保存），程序化跑完 **104 命中（14.8%）**。命中集中在单调用、不超过 32 字节的函数（c1 99/338；不超过 32 字节 86/191），多调用/大函数几乎不中。
> - **likely 指令 174 个**：给 tools/branch_gen.py 加了 likely 模板（延迟槽只在分支成立时执行），跑完 **0 命中**。
> - **unaligned（ldl/ldr/sdl/sdr）173 个**：现有模板只有 3 个能生成候选、编译后 0 命中；LLM 一轮结果见第 4 节。
> - 验收：见第 5 节。

---

## 1. 本轮做了什么

| # | 动作 | 产物 |
|---|---|---|
| 1 | 写 tools/call_gen.py，跑 hard 702 个调用类函数 | tools/call_gen.py、build/m2-5-call-results.json |
| 2 | 给 branch_gen.py 加 likely 模板，跑 174 个 | tools/branch_gen.py、build/m2-5-branch-results.json |
| 3 | unaligned 173 个：现有模板 + LLM 各跑一轮 | build/m2-5-unaligned-results.json、build/m2-5-unaligned-llm.json |
| 4 | 验收与文档 | build/m2-5-check.log、本报告 |

集合定义在 build/m2-5-sets.json（call702 / likely / unaligned 三组地址）。

---

## 2. hard 调用类 702（call_gen.py）

### 2.1 生成器

call_gen.py 复用 auto_match 的表达式 IR，新增：

- jal FUN_xxx 翻译成 v0 = FUN_xxx(args)；j FUN_xxx 翻译成 return FUN_xxx(args)；
- 调用参数从调用点前的 a0-a3 取值（按实际被写过的寄存器决定个数）；
- 为每个调用生成完整 extern 原型（实参为符号/加载/参数时用 void*，字面量用 int），避免 gcc 2.96 对无原型调用生成栈参数；
- 忽略标准栈帧操作：addiu sp,sp,正负N、sw/lw/sd/ld ra 或 s0-s7, off(sp) 不参与翻译（C 编译器自己生成栈帧），从而让带 prologue 的 hard 函数也能生成候选。

### 2.2 结果

| 指标 | 数值 |
|---|---|
| 函数数 | 702 |
| MATCH | **104（14.8%）** |
| 候选覆盖率 | 约 95%（抽样 60 个里 57 个能生成） |
| 耗时 | 314 秒（生成 + 编译 + 判定） |

按调用数：

| calls | MATCH/总数 | 命中率 |
|---|---|---|
| 1 | 99/338 | 29.3% |
| 2 | 2/102 | 2.0% |
| 3 | 3/262 | 1.1% |

按 size：

| size | MATCH/总数 | 命中率 |
|---|---|---|
| 不超过 32 | 86/191 | 45.0% |
| 33-64 | 16/261 | 6.1% |
| 65-128 | 2/250 | 0.8% |

按 cls：local 83/505、ambiguous 11/126、needs_G8 10/71；padding 命中 0。

### 2.3 失败诊断

1. **尾调用栈帧**：原版 8 字节尾调用（j FUN; addiu a1,...）没有栈帧，而 gcc 2.96 -O2 即使做 sibling call 也会生成 addiu sp,-16; sd ra; ...; ld ra; j; addiu sp,16（已用最小用例复现，试过 void/int/参数匹配均如此），所以这类小尾调用必然 MISS。
2. **栈帧大小/保存顺序**：带 prologue 的函数，C 编译器生成的栈帧布局与原版不同（局部变量、保存寄存器数量），33-64 字节函数命中率骤降。
3. **多调用寄存器分配**：c2-3 的 2-3 次调用之间 gcc 重排、寄存器复用，命中率只有 1-2%。
4. **padding**：hard 中带尾部对齐 nop 的调用函数命中 0（core-only 门尚未接入 call_gen 的 overrides）。

---

## 3. likely 指令 174（branch_gen 扩展）

给 branch_gen.py 加 render_likely()：

- 识别 beql/bnel/bltzl/bgezl/bgtzl/blezl/beqzl/bnezl；
- 延迟槽指令只在分支成立时执行，fallthrough 路径跳过它；
- 生成 if (cond) { delay + then } else { fallthrough } 两路模板；
- 两路各自翻译到 jr（含 jr 延迟槽）。

结果：**174 个全部 MISS（0/174）**。原因：

- 大量 bgezl/bgtzl 是硬件轮询循环（延迟槽做计数器递减、循环体是 nop），普通 C 无法表达 volatile 语义；
- 多返回点（multi-return）与两路各自的 jr 调度，gcc 生成的代码形态与原版不同；
- likely 的延迟槽调度是 gcc 的 likely 启发式，C 源码层面难以强制。

---

## 4. unaligned 173（ldl/ldr/sdl/sdr）

### 4.1 现有模板

对 173 个分别跑 auto_match / branch_gen / call_gen 的生成器：

| 指标 | 数值 |
|---|---|
| 有候选 | **3 / 173** |
| 编译候选 | 16 |
| MATCH | **0** |

其余 170 个直接 Unsupported（生成器不支持 ldl/ldr/sdl/sdr）。

### 4.2 LLM 一轮

| 模式 | 样本 | 命中 | 说明 |
|---|---|---|---|
| fast + batch=4（thinking off） | 172 / 173 | **0** | 最后 1 个请求挂起后终止；候选被 volatile/goto/编译失败大量丢弃 |

LLM 对该组同样无解：生成器/模型都倾向于生成 ld/sd 或结构体访问，无法得到 ldl/ldr/sdl/sdr 形态。

### 4.3 结论

ldl/ldr/sdl/sdr 是 MIPS 的非对齐 64 位访问指令。普通 C 的 long long 访问在 -O2 下默认假设对齐，生成 ld/sd；要生成 ldl/ldr 需要编译器判定访问非对齐，C 源码层面几乎不可控。这组函数需要单独决定是否允许 memcpy 形态或内建，否则应在硬档中排除。

---

## 5. 验收

| 检查 | 结果 |
|---|---|
| python tools/build.py overrides | **223 matched / 0 todo / 223 total**，全部 MATCH |
| make check | **RESULT: MATCH**；SHA-256 一致；**223 个函数 / 5,008 字节**来自 C |
| 本轮新增 overrides | **104** 个 hard 调用类函数（call_gen） |

---

## 6. 诚实边界

1. **702 命中 14.8%** 全部来自程序化模板，不涉及 LLM；命中集中在小函数，不能外推到 hard 全档。
2. **likely 0/174、unaligned 0/173**：这两组是 triage 的 unsupported 标记，普通 C 模板覆盖不到；报告如实记录，不代表它们不可匹配（需要专门处理）。
3. **栈帧忽略是近似**：call_gen 忽略 sp 保存/恢复，让 C 编译器自己生成栈帧；栈帧大小/保存顺序与原版不一致时仍会 MISS，这正是多调用/大函数命中率低的主因。
4. **padding 门**：call_gen 未接入 core-only 台账，带尾部 nop 的命中为 0。

---

## 7. 下一步

1. **call_gen 栈帧对齐**：从原版 prologue 反推局部变量数量/保存寄存器集合，生成匹配的声明顺序；或接受 core-only 门。
2. **尾调用**：用 gcc 的 sibling-call 之外的方式处理，或直接把这些 8 字节桩判为不可匹配。
3. **likely/unaligned**：从 hard 档中单列，等专门方案（内建函数/结构体布局/汇编级例外）。
4. **hard 后续批次**：c1+b0+padding（118）、c2-3+b1（98）等。

---

## 8. 产物清单

| 路径 | 说明 |
|---|---|
| tools/call_gen.py | 核心交付物：jal/j 调用生成器 |
| tools/branch_gen.py | 扩展：likely 模板 |
| build/m2-5-sets.json | 三组地址集合 |
| build/m2-5-call-results.json | 702 逐条结果 |
| build/m2-5-branch-results.json | likely 174 结果 |
| build/m2-5-unaligned-results.json | unaligned 程序化尝试 |
| build/m2-5-unaligned-llm.json | unaligned LLM 尝试 |
| build/m2-5-*.log | 运行日志 |
