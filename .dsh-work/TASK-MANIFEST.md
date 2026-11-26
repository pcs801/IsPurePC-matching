# 任务产出清单

## m26b8-tu-001064d8（PS2 MIPS TU 字节匹配 worker，TU tu/001064d8）

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
| --- | --- | --- | --- | --- |
| 03:50 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00106668.c | 本任务候选源码（FUN_00106668） | 中间产物 | 保留 |
| 03:50 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_001064d8\disdiff.py | 本任务差异对照脚本 | 临时文件 | 保留至任务结束 |
## m26b8-tu-00107d88（PS2 MIPS TU 字节匹配 worker，TU tu/00107d88）

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
| --- | --- | --- | --- | --- |
| 04:10 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00107db8.c | 本任务候选源码（FUN_00107db8，224/224 字节仅 jump table 基址 2 字不同） | 中间产物 | 保留 |
| 04:10 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00107ed8.c | 本任务候选源码（FUN_00107ed8，88/84 字节，diff 为 jal/lw 延时槽位置） | 中间产物 | 保留 |
| 04:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00107d88\result.json | 本 TU 结果汇总（2 MISS + 诊断） | 交付物 | 保留 |
| 04:10 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00107d88\matched.md | 本 TU 命中记录（本次 0 命中，写入诊断说明） | 交付物 | 保留 |
| 04:10 | E:\ONE PIECE\S\IsPurePC-matching\build\scratch\probe.c/probe2.c/probe3.c/cmp.sh/p3.sh | 编译器调度探针脚本 | 临时文件 | 已删除 |
## m26b8-tu-00104e20（PS2 MIPS TU 字节匹配 worker，TU tu/00104e20）

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
| --- | --- | --- | --- | --- |
| 03:57 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00105f58.c | 本任务产出，0x00105F58 匹配源码（MATCH） | 交付物 | 保留 |
| 04:14 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00108590.c | 本任务产出，0x00108590 最佳候选（428/432，MISS） | 中间产物 | 保留（供复核） |
| 04:17 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00105fb8.c | 本任务产出，0x00105FB8 部分还原（MISS） | 中间产物 | 保留（供复核） |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00104e20\result.json | 本任务交付，3 函数结果 | 交付物 | 保留 |
| 04:00 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00104e20\_probe.py、_probe_multi.py | 本任务调试脚本（编译+反汇编 diff 探针） | 临时文件 | 保留（可复用） |
| 04:02 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00104e20\v\*.c | 本任务候选变体（约 20 个） | 临时文件 | 移入回收（待收尾） |
| 03:57 | E:\ONE PIECE\S\IsPurePC-matching\build\candidates\probe_*\ | 探针编译产物 | 临时文件 | 移入回收（待收尾） |
## m26b8-tu-00104e48（PS2 MIPS TU 字节匹配 worker，TU tu/00104e48）

| 时间 | 文件绝对路径 | 来源与用途 | 类别 | 最终处置 |
| --- | --- | --- | --- | --- |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00105c20.c | 本任务产出，0x00105C20 匹配源码（MATCH，1 次） | 交付物 | 保留 |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00106e90.c | 本任务产出，0x00106E90 最佳候选（280/280 字节，仅 4 字调度差，MISS） | 中间产物 | 保留（供复核） |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\src\functions\00106fa8.c | 本任务产出，0x00106FA8 部分还原（MISS，跳转表 section reloc 不可解析） | 中间产物 | 保留（供复核） |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00104e48\matched.md | 本 TU 命中记录（追加 FUN_00105C20） | 交付物 | 保留 |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\build\m26-tu\tu_00104e48\result.json | 本 TU 结果汇总（3 函数） | 交付物 | 保留 |
| 04:20 | E:\ONE PIECE\S\IsPurePC-matching\build\_dbg_diff.py、_variants.py、_variants2.py | 本任务调试脚本（编译+逐字 diff 探针） | 临时文件 | 已删除 |
