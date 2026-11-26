# IsPurePC-Matching

PS2《I's Pure》(SLPM-66570, 2006, Regista / Takara Tomy) 的**字节级 matching decompilation** 项目。

- 判定：每个函数的编译字节与原版相等（objdiff）；未匹配函数用原版字节补齐。
- 完成线：函数级 ≥95%，行为 100%。
- 编译器：SCE ee-gcc 2.96（实测指纹见 `docs/PLAN.md`）。

## 从哪读起

1. `docs/PLAN.md` — 目标、选型、里程碑、旧项目资产利用
2. `docs/STATE.json` — 当前阶段
3. `docs/HANDOFF.md` — 下一个会话的启动指令（**新会话先读这个**）

## 目录

```
baserom/   原版 ELF（不入库）        ← 待建
config/    符号/切分/工具链配置
asm/       splat 拆分产物（不入库）
src/       匹配中的 C
include/   结构体与声明
tools/     工具
progress/  进度报告
docs/      计划与交接
```

## 状态

M0 spike 已通过（2026-11-26）：11/11 函数与 baserom 字节一致；M1 进行中（-G 普查完成、.text 整段重建重定位外 0 差异），\`-O2 -mips3\`，\`-G\` 按 TU 混合（7 个无关 / 1 个 -G0 / 3 个 -G8）。当前进入 M1 骨架。见 \`docs/spike-report.md\`。
