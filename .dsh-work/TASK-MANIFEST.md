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

## m26b10-tu-0010c230（PS2 matching：TU tu/0010c230 函数字节匹配）
目标：把 TU tu/0010c230 的 1 个函数（0x0010C230）匹配到字节一致。

| 时间 | 文件（绝对路径） | 来源/用途 | 类别 | 处置 |
| --- | --- | --- | --- | --- |
| 04:20 | E:\\ONE PIECE\\S\\IsPurePC-matching\\src\\functions\\0010c230.c | 本任务手写 C 候选（最终 MATCH） | 交付物 | 保留 |
| 04:20 | E:\\ONE PIECE\\S\\IsPurePC-matching\\build\\m26-tu\\tu_0010c230\\matched.md | 命中源码归档 | 交付物 | 保留 |
| 04:20 | E:\\ONE PIECE\\S\\IsPurePC-matching\\build\\m26-tu\\tu_0010c230\\result.json | 每函数结果汇总 | 交付物 | 保留 |
| 04:20 | E:\\ONE PIECE\\S\\IsPurePC-matching\\build\\m26-tu\\tu_0010c230\\dump.py / iterate.py / iterate2.py / iterate3.py | 反汇编与变体批量比对脚本 | 临时文件 | 删除 |
| 04:20 | E:\\ONE PIECE\\S\\IsPurePC-matching\\build\\candidates\\{check_10c230,tu10c230,tu10c230v,tu10c230w,tu10c230x}\\ | pipeline 编译中间产物 | 中间产物 | 保留（仓库常规构建产物，与其它 TU 并存） |
| 04:40 | E:/ONE PIECE/S/IsPurePC-matching/build/m26-tu/tu_00104e48/showdiff.py | 自建：编译单函数并与 ROM 逐字比对 + objdump 反汇编列出（pipeline 自带 disasm 因路径 bug 恒为空） | 中间产物 | m26 tu/00104e48 字节匹配 | 保留（TU 沙箱工具） |
| 04:40 | E:/ONE PIECE/S/IsPurePC-matching/build/m26-tu/tu_00104e48/expdump.py, exp.c | 自建：C 片段快速编译+反汇编实验（abs/尾调用形态探测） | 临时文件 | 同上 | 可删 |
| 04:40 | E:/ONE PIECE/S/IsPurePC-matching/src/functions/001071b0.c, 00107758.c, 00107990.c | 三个候选 C 源（00107758 已 MATCH） | 交付物 | 同上 | 保留 |
| 04:40 | E:/ONE PIECE/S/IsPurePC-matching/build/m26-tu/tu_00104e48/matched.md, result.json | 命中源码累积与逐函数结果 | 交付物 | 同上 | 保留 |
