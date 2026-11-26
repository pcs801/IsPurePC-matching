# splat 接入（M1）

> 执行：2026-11-26
> splat 0.50.1（spimdisasm 1.42.4）+ ee-gcc 2.96 / ee-as 2.10

## 1. 结论

| 项 | 结果 |
|---|---|
| .text 拆分 | **成功**：`asm/1000.s`，17.8 MB，**3968 个 glabel**（3966 符号 + 自动标签），100 个 alabel，492 个 `.word` |
| 重建 | `ee-as` 汇编后 `.text` = **1,124,764 字节，与 baserom 完全等长** |
| 字节比对 | 15,488 处重定位：**opcode/寄存器 0 处不符**；**重定位之外的字节差异 = 0** |
| 链接脚本 | `link.ld` 已生成（text 段 0x100000，按 subsegment 分 .text/.data/.rodata） |
| objdiff | **可用**：`objdiff-cli diff -1 build/splat/1000.o -2 <base.o> FUN_00102078` → `match_percent: 100` |

## 2. 配置（`splat.yaml`）

```yaml
platform: ps2
compiler: EEGCC                 # 必须；默认 IDO 会按 N64 处理
asm_path: asm
symbol_addrs_path: config/symbol_addrs.txt
segments:
  - [0x0, bin]                  # ELF header
  - name: text
    type: code
    start: 0x1000               # rom offset
    vram: 0x00100000
    subsegments:
      - [0x1000, asm]
  - [0x11399C]                  # ← 必须的 rom end marker
```

## 3. 三个坑（按排查顺序）

### 3.1 段列表必须以 `[rom_end]` 结束

不加这个单元素列表时，`splat` 报 `UnboundLocalError: next_start`（最后一段没有终点），或静默把段长算成 0（`Split 0 B`）。
源码位置：`splat/scripts/split.py` → `initialize_segments`，日志提示是
`"Segments list must end with a rom end pos marker ([0x10000000])"`。

### 3.2 `compiler` 必须是 `EEGCC`

默认是 `IDO`。EEGCC 会启用 `align_on_branch_labels`，并选对 32 位小端 MIPS 的宏/汇编方言。

### 3.3 ★ 任何 < 8 字节的函数会让 splat 级联退化成 `.word`

**现象**：完整 3,967 符号表时，只有 185 个 glabel；从某个地址起全部变成
`alabel` + `.word`（不反汇编），后续 3,800 多个函数一起废掉。

**定位过程**：
1. 最小符号集（5 个函数）→ glabel 4624，完全正常。
2. 对比发现崩溃点前一个函数 `FUN_0010d320` 的 size = **4 字节**（一条指令）。
3. 删掉这一个符号 → glabel **3968**，恢复正常。

**原因**：spimdisasm 把 < 2 条指令的“函数”判为无效入口，随后把紧随其后的所有符号当作
“函数内部标签”（`ASM_TEXT_ALT_LABEL` = `alabel`），整段停止反汇编。

**修复**（已写进 `tools/make_symbols.py`）：把 `size < 8` 的符号**并入前一个函数**
（`prev.size += tiny.size`），而不是丢弃 —— 保持地址覆盖连续。

### 3.4 旧符号表尺寸重叠

旧项目 `_index.tsv` 的 size 是独立分析产物，互相重叠（splat 会警告
`symbol X overlaps with Y` 并退化）。`make_symbols.py` 已改为
**size = next_symbol_addr - addr**（最后一个到 `.text` 末尾），2,515 个尺寸被修正。

## 4. 汇编适配（ee-as 2.10 比现代 gas 老）

### 4.1 macro.inc 必须改写

splat 生成的宏用 `"\label"` 引号和 `\().` 拼接、`.internal`、`.aent`，2.10 全部不认
（报 `no such section` / `Unknown pseudo-op`）。
项目 `include/macro.inc` 已替换为兼容版：无引号、无 `.internal`、无 `.aent`、无
`.ent/.end`（`.ent` 嵌套会报 `second .ent directive`；去掉不影响 `.text` 字节）。

### 4.2 MMI 助记符要兜底

spimdisasm 会把 R5900 的 MMI 指令输出成 `padduw/daddu/mult ...`，**ee-as 2.10 不支持**
（`illegal operands`）。但 `.word 0x...` 可以。

做法：`tools/fix_asm.py`（待固化）迭代汇编 → 收集 `Error:` 行 → 把该行替换为
`.word`（数值取自行尾注释的原始 word，做字节反转）→ 再汇编，直到 0 错误。
本次共替换约 2.6 万行，最终 0 error。

> 说明：这些行本来就是 spimdisasm 猜的指令，替换成 `.word` 后**字节完全保真**，
> 不影响重建结果。

## 5. 产物

| 文件 | 说明 |
|---|---|
| `asm/1000.s` | splat 拆出的 .text（17.8 MB，不入库） |
| `link.ld` | 链接脚本（text 段 0x100000） |
| `config/undefined_funcs_auto.txt`, `undefined_syms_auto.txt` | splat 生成的未定义符号 |
| `build/splat/1000.o` | ee-as 汇编产物（1.49 MB，带 4,129 符号 + 15,488 重定位） |
| `build/splat/1000.fixed.s` | 替换过 .word 的 asm |

## 6. 复现

```bash
python tools/make_symbols.py                  # 生成 config/symbol_addrs.txt
python -m splat split splat.yaml              # 拆 .text -> asm/1000.s
# 复制 asm/1000.s + include/macro.inc 到 WSL /root/work/asmtest/
# 迭代：ee-as 汇编 -> 报错行改 .word -> 直到 0 错误
python tools/verify_reloc_aware.py            # 重定位感知比对
```

## 7. 后续（M1 剩余）

1. 把 `fix_asm.py` 固化进 `tools/`（当前是 /tmp 一次性脚本，需重写为仓库脚本）。
2. 链接：当前无 `ee-ld`（工具链只有 cc1+as）。要产出最终镜像需 ps2dev 的 ee-binutils，
   或用重定位感知比对代替（当前已达到「重定位外 0 差异」）。
3. `.data/.rodata/.sdata/.bss` 段尚未拆分，只做了 `.text`。
4. objdiff 的工程化：`objdiff.json` + 符号名映射（splat 用 `FUN_xxx`，C 侧要同名）。
