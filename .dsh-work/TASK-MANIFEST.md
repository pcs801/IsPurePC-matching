# TASK-MANIFEST (m26b9-tu-00107d88)

任务：TU tu/00107d88 三个 PS2 MIPS 函数字节级匹配（工作区 E:/ONE PIECE/S/IsPurePC-matching）

| 时间 | 文件 | 来源/用途 | 类别 | 处置 |
|---|---|---|---|---|
| 05:10 | build/_m26_dis.py | 自建并排反汇编对比脚本 | 临时文件 | 保留（供后续 worker 复用） |
| 05:10 | build/_m26_orig.py | 自建 baserom 原始函数反汇编 | 临时文件 | 保留 |
| 05:10 | tools/_m26_shape.py | 自建规范化结构差异工具 | 临时文件 | 保留 |
| 05:10 | tools/_m26_try.py | 自建批量候选编译比对工具 | 临时文件 | 保留 |
| 05:10 | build/_m26_spec.json | 批量试验输入（临时） | 临时文件 | 保留 |
| 05:10 | build/candidates/try*/、check_*/ | 编译产物缓存 | 中间产物 | 保留 |
| 05:10 | src/functions/00107f30.c | 最终源码（MATCH） | 交付物 | 保留 |
| 05:10 | src/functions/001080a0.c | 最佳候选（MISS，34 差异） | 交付物 | 保留 |
| 05:10 | src/functions/001081f8.c | 最佳候选（MISS，138 差异） | 交付物 | 保留 |
| 05:10 | build/m26-tu/tu_00107d88/matched.md | 已命中源码累积 | 交付物 | 保留 |
| 05:10 | build/m26-tu/tu_00107d88/result.json | TU 结果 | 交付物 | 保留 |
