# 任务产出清单


## t193 (0x00167568 case idx6/7) — 02:56
- `src/functions/00167568.c` — 累积写：骨架 + case idx0（并修正其尾部调用）+ case idx6/7；来源：反汇编 0x1677F8-0x1678F4；类别：交付物（源码，待统一 verify）；处置：保留
- `build/m26-tu/tu_00167568/result.json` — TU 记录（追加 case 6/7 块条目）；类别：中间产物/记录；处置：保留
- `build/_dis_167568.txt` — 反汇编导出（t175 期间生成）；类别：临时文件；处置：保留（后续统一 verify 还要用）

## t198 (0x00167568 case idx1/2) — 03:03
- `src/functions/00167568.c` — 累积写：新增 case 1/2（守卫 + 单次 append 尾部）；来源：反汇编 0x1678F8-0x1679F4；类别：交付物（源码，待统一 verify）；处置：保留
- `build/m26-tu/tu_00167568/result.json` — TU 记录（追加 case 1/2 块条目）；类别：中间产物/记录；处置：保留

## t200 (小函数批：4 个 16B syscall stub) — 03:12
- `src/functions/00205690.c` / `002056a0.c` / `002056b0.c` / `002056c0.c` — 占位实现 + 说明注释（目标为 syscall stub，纯 C 不可生成）；类别：交付物（占位）；处置：保留
- `build/m26-small/t200.json` — 本批结论记录（4/4 不可匹配 + 证据）；类别：中间产物/记录；处置：保留

## t204 (小函数批 set 1：4 个) — 03:23
- `src/functions/001b4c18.c` / `001cffe8.c` / `001d1198.c` — 命中实现（MATCH g=0）；类别：交付物；处置：保留
- `build/m26-small/t204.json` — 本批结论（3 MATCH + 1 known-hard + 关键写法）；类别：记录；处置：保留
- `build/_v1b4c18.json` / `build/_probe_1b4c.py` — 变体探针（临时）；类别：临时文件；处置：保留（写法可复用）

## t207 (小函数批 set 4：4 个) — 03:34
- `src/functions/001ab618.c` / `001ab638.c` / `001b47e8.c` / `001b7ef8.c` — 4 个命中实现（MATCH g=0）；类别：交付物；处置：保留
- `build/m26-small/t207.json` — 本批结论 + **单调用包装 vs sibcall 的解法**（do-while 包装）；类别：记录；处置：保留
- `build/_vt207.json` / `build/_probe_t207.py` — sibcall 试探脚本（临时）；类别：临时文件；处置：保留（经验已入记录）

## t216 (小函数批 set 2：5 个) — 03:44
- `src/functions/0020ce70.c` / `0020d2c0.c` / `0020dd90.c` / `0020e888.c` / `0020e8a8.c` — 5 个命中实现（MATCH g=0，全部一次通过）；类别：交付物；处置：保留
- `build/m26-small/t216.json` — 本批结论（5/5 + do-while 规则验证 + 栈缓冲参数扩展）；类别：记录；处置：保留

## t224 (小函数批 set 7：5 个) — 03:52
- `src/functions/001b68e8.c` / `001b6910.c` / `001b6938.c` / `001b6b68.c` / `001b6bf0.c` — 5 个命中（MATCH g=0，全部一次通过）；类别：交付物；处置：保留
- `build/m26-small/t224.json` — 5/5 记录 + 两条新模式（守卫式函数指针回调、多调用尾调用）；类别：记录；处置：保留

## playbook 汇总（cracker-2，t204/t207/t216/t224 经验） — 03:56
- `build/m26-small/PLAYBOOK-small-functions.md` — 小函数匹配 6 条规则汇总（纯包装 do-while、栈缓冲、守卫回调、多调用尾调用、早退写法、asm-only 清单）；类别：记录（团队共享）；处置：保留

## t230 (小函数批 set 11：5 个) — 04:12
- `src/functions/001f5bb0.c` — **MATCH g=0**（`return (r == -1) ? 0 : r;`，movz 语义）；类别：交付物；处置：保留
- `src/functions/001e1d60.c` / `001e1dc0.c` / `001eab38.c` / `001eab60.c` — 近失版本（4 / 10 / 2 / 2 词差）；类别：交付物（near-miss）；处置：保留
- `build/m26-small/t230.json` — 5 条结果 + 每条的差异根因与已试写法；类别：记录；处置：保留

## t237 (小函数批 set 12：5 个) — 04:20
- `src/functions/001cc338.c` — **MATCH g=0**（`p->fC4 = v; p->fC8 = v / 0x600;`）；类别：交付物；处置：保留
- `src/functions/001ac710.c` — 近失（44/44、2 词差：GCC 把 -1 重写成 -625）；类别：交付物（near-miss）；处置：保留
- `src/functions/001be878.c` / `001c1d98.c` / `001cc2d8.c` — 硬墙占位（空延时循环被删 / splat 把 6 个访问器并成 48B）；类别：交付物（占位）；处置：保留
- `build/m26-small/t237.json` — 5 条结果与根因；类别：记录；处置：保留

## playbook 追加规则 7（空变参函数） — 04:26
- `build/m26-small/PLAYBOOK-small-functions.md` — 追加「空变参函数直接写 `void f(int a, ...) { }`」一条（t242 经验）；类别：记录（团队共享）；处置：保留

## playbook 追加规则 8（非对齐 struct 拷贝） — 04:30
- `build/m26-small/PLAYBOOK-small-functions.md` — 追加「非对齐 8 字节拷贝用 struct S8 拷贝表达，ldl/ldr/sdl/sdr 非 asm-only」（t247 经验）；类别：记录（团队共享）；处置：保留

## playbook 回验更新（cache / ldl-ldr） — 04:34
- `build/m26-small/PLAYBOOK-small-functions.md` — 规则 6 增补 `cache` 仍 asm-only；规则 8 标注 0x001D1230 MATCH 已验证；类别：记录（团队共享）；处置：保留

## playbook 追加规则 9（指令分类最终版） — 04:38
- `build/m26-small/PLAYBOOK-small-functions.md` — 新增 9 节：可写（ldl/ldr/sdl/sdr、空变参）vs 不可写（lq/sq、cache/mfc0/ei/sync/syscall），并记录 0x001E3FA8 实为 cache 的 sig 误标；类别：记录（团队共享）；处置：保留
