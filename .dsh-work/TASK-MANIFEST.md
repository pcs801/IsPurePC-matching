# 任务产出清单（单一文档，逐任务追加）

## 2026-11-26 M2.1：build.py per-function override + 手跑 5 个 local 函数

一句话目标：让 build.py 支持 config/overrides.json 的逐函数 C 覆盖（C 编译字节替换 asm 字节并逐字节校验），并用 5 个 local 类函数跑通「写 C → 编译 → 比对」循环，验收 make check 仍 SHA 一致。

结果：**通过**。`make check` = RESULT: MATCH，SHA-256 `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147`（其中 5 个函数 / 104 字节来自 C）。

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
|---|---|---|---|---|
| 13:40 | E:\ONE PIECE\S\IsPurePC-matching\.dsh-work\TASK-MANIFEST.md | 本清单 | 交付物（流程） | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\tools\build.py | 修改：新增 overrides 步骤（WSL 编译 → 重定位解析 → 字节比对 → 拼接 + 失败即构建失败） | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\config\overrides.json | 新增：5 条 matched 覆盖记录 | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00155b68.c | 新增：手写匹配源码（两个 int store） | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00177c28.c | 新增：手写匹配源码（0x168/0x16c 清零） | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\0019b590.c | 新增：手写匹配源码（两字段 ×2） | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\001a8208.c | 新增：手写匹配源码（a<<12 两处 + 5 store） | 交付物 | 保留 |
| 13:42 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\001a82a8.c | 新增：手写匹配源码（定点相等判断） | 交付物 | 保留 |
| 13:44 | E:\ONE PIECE\S\IsPurePC-matching\build\probe\*（probe.c / probe.o / probe2.c / probe2.o / analyze.py / analyze2.py / perms.json） | 语句顺序搜索探针（132 个变体） | 临时文件 | **已删除**（13:53） |
| 13:47 | E:\ONE PIECE\S\IsPurePC-matching\build\overrides\*.G0.o | 5 个覆盖函数的编译中间产物（可重建） | 中间产物 | 保留（build/ 已 gitignore） |
| 13:47 | E:\ONE PIECE\S\IsPurePC-matching\build\_wsl_overrides.sh | 构建脚本（每次运行自动重生成） | 中间产物 | 保留（build/ 已 gitignore） |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\tools\__pycache__\build.cpython-310.pyc | py_compile 语法检查副产物 | 临时文件 | **已删除**（13:53） |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\progress\ledger.tsv | 修改：追加 5 条 MATCH + 1 条 REJECTED（0x00112BF8 需 volatile） | 交付物 | 保留 |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\docs\build.md | 修改：新增 §4 per-function override，链路改 6 步，命令加 overrides | 交付物 | 保留 |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\docs\STATE.json | 修改：gate m2_1_overrides=passed，next_action=M2.2 | 交付物 | 保留 |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\docs\HANDOFF.md | 修改：阶段 M2.1 完成、命令与匹配循环更新 | 交付物 | 保留 |
| 13:48 | E:\ONE PIECE\S\IsPurePC-matching\Makefile | 修改：新增 `overrides` 目标 | 交付物 | 保留 |

清理报告：删除临时文件 8 个（build/probe 下 7 个 + tools/__pycache__ 1 个，均为本任务生成的可重建调试产物）；移入回收 0 个；保留交付物 12 项、中间产物 2 类（build/overrides/、build/_wsl_overrides.sh）。

## 2026-11-26 M2.3：剩余 89 个 easy + llm_match.py（证据卡 + LLM）+ medium 195

一句话目标：先把 easy 档剩余 89 个跑完，再写 tools/llm_match.py（证据卡 → LLM 生成 C → match_kit 字节判定循环）并跑 medium 195 个统计命中率。

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
|---|---|---|---|---|
| 19:58 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-easy.log | 剩余 89 个 easy 的批次日志 | 关键证据 | 保留（build/ 不入库） |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\tools\llm_match.py | **核心交付物**：证据卡 + LLM(Anthropic Messages) + match_kit 判定循环 | 交付物 | 保留 |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\config\llm.local.json | LLM 端点/模型本地配置（凭证不入库） | 配置 | 保留（gitignore） |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\build\llm-evidence\* | 未命中函数的证据卡 + LLM 原始回复 | 中间产物 | 保留（证据） |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-llm-results.json | medium 195 逐条结果与统计 | 关键证据 | 保留 |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-llm.log | medium 运行日志 | 关键证据 | 保留 |
| 20:00 | E:\ONE PIECE\S\IsPurePC-matching\docs\m2-3-llm.md | M2.3 报告（方法/命中率/诚实边界） | **核心交付物** | 保留 |

### M2.3 结果（21:12）

结果：easy 139 全跑完 → **107 MATCH（77.0%）**，本轮 89 → 67；llm_match.py 跑 medium 195 → 纯 LLM **44（22.6%）** + 程序化 baseline **33** = **77（39.5%）**（7 字节全等 + 70 core-only）；overrides **118/118 MATCH**；make check **SHA 一致**（118 函数 / 1,832 字节来自 C）。

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
|---|---|---|---|---|
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-medium-summary.json | fast + baseline 合并统计（按 flags/size/cls） | 关键证据 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-llm-padded.json | 70 个 core-only 命中台账 | 交付物 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-deep.log | thinking 模式实验日志（网关空文本/budget 失效） | 证据 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-check.log | make check 验收日志 | 关键证据 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-3-progress.log | make progress 上传日志（HTTP 201） | 证据 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\docs\progress.html | 仪表盘（make progress） | 交付物 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\docs\STATE.json、docs\HANDOFF.md | 阶段 M2.3 完成、gate、下一步 M2.4 | 交付物 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\progress\ledger.tsv | 追加本轮 77 条命中 | 交付物 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\config\overrides.json | 118 条 matched | 交付物 | 保留 |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\candidates\ | 候选 C / .o / .err / .dis（约 19MB） | 中间产物 | 保留（build/ 不入库，可复查） |
| 21:10 | E:\ONE PIECE\S\IsPurePC-matching\build\llm-evidence\ | 未命中函数的证据卡历史 | 中间产物 | 保留 |

清理报告：删除本任务临时文件（build/_card.txt、build/_diag.py、build/_m23_baseline.py、build/_m23_merge.py、build/_payload.json、build/_resp.json、build/_wsl_match_m23*.sh、build/_wsl_objdump_*.sh、tools/__pycache__/*.pyc）；移入回收 0 个；保留交付物 8 项、关键证据 6 项、中间产物 2 类（build/candidates、build/llm-evidence）。

## 2026-11-26 M2.4：thinking 上限 + 分支生成器 + hard 分类

一句话目标：① 对 medium 漏检函数用 thinking + batch=1 重跑测上限；② 写分支生成器（if/else、switch、循环）；③ 把 hard 3,632 个按大小/分支数/FPU/调用数细分。

结果：
- ① thinking 模式受网关限制：长 prompt 随机挂起，仅得到 7 个有效样本（3 个 thinking + 4 个 fast batch=1），0 命中；118 个未全量。
- ② 分支生成器 tools/branch_gen.py：57 个未命中分支函数验证，命中 2 个（0x001CD4B8、0x001CFFA0），累计分支覆盖 17/72（23.6%）。
- ③ hard 分类：3,632 个 → build/hard-classes.json（size/branches/calls/FPU/syscall/unsupported 四维 + 交叉表）。
- 验收：python tools/build.py overrides → 119/119 MATCH；make check → SHA 一致（119 函数 / 1,856 字节来自 C）。

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
|---|---|---|---|---|
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\tools\branch_gen.py | 核心交付物：if/else + switch/if-链 + 循环模板 | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\tools\hard_classes.py | 核心交付物：hard 档四维分类 | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\hard-classes.json | 3,632 函数分类结果 | 交付物 | 保留（build/ 不入库） |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-4-branch-results.json | 57 个分支函数验证结果 | 关键证据 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-4-deep-results.json | thinking 3 样本结果 | 关键证据 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-4-deep3.log、m2-4-deep-fast.log | thinking/fast 样本日志 | 证据 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-4-branch.log、m2-4-check.log、m2-4-progress.log | 分支/验收/上传日志 | 证据 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\docs\m2-4-control-flow.md | M2.4 报告 | 核心交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\docs\progress.html、STATE.json、HANDOFF.md | 阶段 M2.4、仪表盘、交接 | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\config\overrides.json | 119 条 matched | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\progress\ledger.tsv | 追加 2 条分支命中 | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\001cd4b8.c、001cffa0.c | 分支生成器命中源码 | 交付物 | 保留 |
| 22:00 | E:\ONE PIECE\S\IsPurePC-matching\build\candidates\（m24*） | 编译中间产物 | 中间产物 | 保留（build/ 不入库） |

清理报告：删除本任务临时文件（build/_m24_deep.py、build/_m24_merge_branch.py、build/m2-4-branch-src/、tools/__pycache__/branch_gen、hard_classes 的 pyc）；移入回收 0 个；保留交付物 10 项、关键证据 5 项、中间产物 1 类（build/candidates）。

## 2026-11-26 M2.5：hard 调用类 702 + likely/unaligned 救援

一句话目标：① 跑 hard 的 c1+b0（338）+ c2-3+b0（364）共 702 个；② likely 174 与 unaligned 173 两组单独救援。

结果：
- ① 新写 tools/call_gen.py（jal/j → extern 原型 + 普通调用，忽略标准栈帧），702 个 → 104 MATCH（14.8%）：c1 99/338（29.3%），size≤32 86/191（45%），多调用仅 1-2%。
- ② likely 174：branch_gen 加 likely 模板后 0 命中；unaligned 173：现有模板 3 个有候选、0 命中，LLM 0/172。
- 验收：python tools/build.py overrides → 223/223 MATCH；make check → SHA 一致（223 函数 / 5,008 字节来自 C）。

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
|---|---|---|---|---|
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\tools\call_gen.py | 核心交付物：jal/j 调用生成器 | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-sets.json | call702 / likely / unaligned 三组地址 | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-call-results.json | 702 逐条结果 | 关键证据 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-branch-results.json | likely 174 结果 | 关键证据 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-unaligned-results.json | unaligned 程序化尝试 | 关键证据 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-unaligned-llm.json（若生成） | unaligned LLM 尝试 | 证据 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m2-5-*.log | 运行/验收日志 | 证据 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\docs\m2-5-hard-calls.md | M2.5 报告 | 核心交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\docs\progress.html、STATE.json、HANDOFF.md | 阶段 M2.5、仪表盘、交接 | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\config\overrides.json | 223 条 matched | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\progress\ledger.tsv | 追加 104 条 hard 命中 | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\*.c | call_gen 命中源码（104 个） | 交付物 | 保留 |
| 23:00 | E:\ONE PIECE\S\IsPurePC-matching\build\candidates\（m25*） | 编译中间产物 | 中间产物 | 保留（build/ 不入库） |

清理报告：删除本任务临时脚本 build/_m25_unal.py 与新增 pyc；移入回收 0 个；保留交付物 10 项、关键证据 5 项、中间产物 1 类（build/candidates）。

| 2026-11-26T16:47:08.347Z | E:/ONE PIECE/S/IsPurePC-matching/src/functions/001bbdc0.c | 函数匹配候选源（5 个叶函数拼合 48 字节） | 交付物 | m26b2-001bbdc0: 0x001BBDC0 字节匹配 | 保留 |
| 2026-11-26T16:47:08.347Z | E:/ONE PIECE/S/IsPurePC-matching/build/sandbox/001bbdc0/result.json | 匹配结果记录 | 交付物 | 同上 | 保留 |
| 2026-11-26T16:52:30.000Z | E:/ONE PIECE/S/IsPurePC-matching/src/functions/001241d0.c | 函数匹配候选源（40 字节叶函数） | 交付物 | m26b2-001241d0: 0x001241D0 字节匹配（MATCH） | 保留 |
| 2026-11-26T16:52:30.000Z | E:/ONE PIECE/S/IsPurePC-matching/build/sandbox/001241d0/result.json | 匹配结果记录（attempts=1, g=8） | 交付物 | 同上 | 保留 |

## 任务：PS2 MIPS 函数匹配 0x0012B628（worker m26b2-0012b628）

- 时间：01:18
- 交付物（保留）：E:\\ONE PIECE\\S\\IsPurePC-matching\\src\\functions\\0012b628.c（候选源码）
- 交付物（保留）：E:\\ONE PIECE\\S\\IsPurePC-matching\\build\\sandbox\\0012b628\\result.json（结果）
- 临时文件（已删除）：build/candidates/*.o/*.c/*.err、build/_dbg_s.sh、build/_dbg_v.sh、build/_dbg_cmp.py、build/_dbg_words.py、build/candidates/dbg12b628/
- 类别：交付物 + 临时文件；处置：临时已删除，交付物保留
| 01:18 | E:/ONE PIECE/S/IsPurePC-matching/src/functions/001d2af8.c | 0x001D2AF8 函数匹配改写（extern 全局赋值） | 交付物 | m26b3-001d2af8 单函数字节匹配 | 保留 |
| 01:18 | E:/ONE PIECE/S/IsPurePC-matching/build/sandbox/001d2af8/result.json | 匹配结果记录 | 交付物 | 同上 | 保留 |

| 01:36 | E:/ONE PIECE/S/IsPurePC-matching/src/functions/00179db8.c | 0x00179DB8 函数匹配候选源码（extern 全局字节读写，最接近的合法形式） | 交付物 | m26b3-00179db8 单函数字节匹配；结果 MISS | 保留 |
| 01:36 | E:/ONE PIECE/S/IsPurePC-matching/build/sandbox/00179db8/result.json | 匹配结果记录（MISS，attempts=2，g=-8，含第一处差异与 dbr 证据） | 交付物 | 同上 | 保留 |
| 01:36 | E:/ONE PIECE/S/IsPurePC-matching/build/candidates/（exp1/exp2/exp3/dump/dbr/check_179db8） | 本次 30+ 个 C 变体的编译中间产物（WSL ee-gcc 对象与 .err） | 中间产物 | 同上 | 保留（build/ 为生成目录且与并发 worker 共用同名目录，未删除） |

## 任务：PS2 MIPS 函数匹配 0x00179DB8（worker m26b3-00179db8）

- 时间：01:36
- 结论：MISS。编译仅 16/20 字节，sb 被 dbr 填入 jr 延迟槽（lui,lbu,jr,sb），而原始为 lui,lbu,sb,jr,nop。
- 证据：同一份 C 用 `-fno-delayed-branch` 编译得到与原始完全一致的 20 字节 3c0200aa 90438d9b a3838243 03e00008 00000000；受门禁固定的 -O2 下，30+ 种纯 C 形式（数组/指针/临时变量/结构体/位域/union/__builtin_memcpy/显式 return 等）都会被填槽，唯一能阻止填槽的是 volatile 限定目的对象（也是 20 字节全等），而 volatile 被规则禁止。
- 交付物（保留）：上面两行；临时编译产物保留在 build/candidates（未删，避免误删并发 worker 同名目录）。
