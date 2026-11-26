# -G 分布普查（M1）

> 执行：2026-11-26
> 方法：静态扫描 `disasm_text.txt`，按「函数内是否出现 `$gp` 相对访存」判定该 TU 是否启用 small data
> 产出：`build/g-distribution.json`、`build/g-distribution.csv`

## 1. 结论

| 集合 | 总数 | needs_G8 | ambiguous | local |
|---|---:|---:|---:|---:|
| 全函数 | 3,967 | **727 (18.3%)** | 1,714 (43.2%) | 1,526 (38.5%) |
| 叶函数（无调用） | 1,187 | 162 (13.6%) | 425 (35.8%) | 600 (50.5%) |
| **spike 候选**（size<64 且无调用/无 FPU/无未识别字节） | **761** | **76 (10.0%)** | 181 (23.8%) | **504 (66.2%)** |

判定口径：

- `needs_G8`：函数内含 `lw/sw/lb/sb/ld/sd/addiu` 且基址寄存器是 `$gp` → 该 TU 必然 `-G8`（或更大）。
- `ambiguous`：无 gp 访问、但有 `lui + 访存/addiu` 形式的绝对地址访问 → 可能是 `-G0`，也可能是 `-G8` 但符号不在 small data（大对象 / .data）。
- `local`：既无 gp 访问也无 lui 绝对访问 → 与 `-G` 无关（占候选 66.2%）。

## 2. 硬证据：gp 基址

`entry`（0x00100008）实测：

```
00100198  lui   $a0, 0x27
001001ac  addiu $a0, $a0, 0x79f0
001001c0  move  $gp, $a0          # gp = 0x002779F0
```

全部 gp 偏移范围 `[-32748, -27960]`（即 `-0x7FEC .. -0x6D38`），换算地址 = `0x26FA04 .. 0x270CB8`，正好覆盖：

| 段 | 地址 | 说明 |
|---|---|---|
| `.lit4` | 0x26FA00..0x26FB70 | 浮点常量池 |
| `.sdata` | 0x26FB80..0x270A1C | 小数据（3,740 B） |
| `.sbss` | 0x270A80..0x270CC8 | 小 bss（584 B） |

→ **small data 真实存在且被 gp 相对访问**，`-G` 不可能全局为 0。M1 的 `configure.py` 必须支持 per-TU `-G`。

## 3. 地址分布（16KB 桶，全函数）

| 地址区间 | needs_G8 | ambiguous | local | 观察 |
|---|---:|---:|---:|---|
| 0x100000-0x16FFFF | 393 | 265 | 179 | 密集 gp 访问，SDK/核心库区 |
| 0x170000-0x19FFFF | ~40 | ~180 | ~70 | ambiguous 主导，过渡区 |
| 0x1A0000-0x211FFF | **0** | ~800 | ~600 | **完全无 gp 访问**，游戏主程序区 |

> 粗判：**0x1A0000 之后是 `-G0` 的游戏代码，低地址是 `-G8` 的库**。这与 PLAN「SOTC 主程序 -O2 -G0、Loader 用 -G8」的结构同型。
> 注意：该分界是统计意义上的，实际 TU 边界需 M1 用 splat 的符号表/段信息校准。

## 4. 对 configure.py 的建议

1. 默认 `-G0`（沿游戏主程序），但**允许 per-TU 覆盖**。
2. 匹配循环里先试 `-G0`；若函数属 `needs_G8` 集合（查 `build/g-distribution.csv`），直接试 `-G8`。
3. 对 `ambiguous` 函数，两版都试（spike 已证 `0x0010BB88` 这类只有 `-G0` 匹配）。
4. 66% 候选是 `local`，-G 不影响 → 可批量自动匹配，是 M2 自动化的第一批主力。

## 5. 复现

```bash
python tools/g_distribution.py
# -> build/g-distribution.json, build/g-distribution.csv
```
