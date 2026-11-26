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
