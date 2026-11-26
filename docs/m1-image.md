# M1 整镜像拼接与重定位解析

> 执行：2026-11-26
> 结果：**重建 ELF 与 baserom SHA-256 完全一致**
> `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147`

---

## 1. 做了什么

```
splat 拆分 → asm/1000.s + assets/*.bin
        ↓ ee-as 汇编（MMI 用 .word 兜底）
   build/splat/1000.o（带 15,560 条重定位）
        ↓ tools/reloc_resolver.py（符号地址 + 重定位解析）
   build/splat/1000.resolved.bin（.text 最终字节）
        ↓ tools/assemble_image.py（按段偏移拼回 ELF）
   build/splat/SLPM_665.70.rebuilt
        ↓ sha256
   与原版一致
```

| 阶段 | 数据 |
|---|---|
| 重定位总数 | 15,560（R_MIPS_26 ×15,321、R_MIPS_HI16 ×167、R_MIPS_LO16 ×72） |
| 应用成功 | 15,560（0 未解析） |
| .text 字节比对 | **0 差异 / 1,124,764 字节** |
| 拼接段 | 10 段（0x0 header、.text、.ctors/.dtors/.reginfo/.data/.eh_frame/.rodata/.lit4/.sdata） |
| SHA-256 | **一致** |

## 2. 重定位解析规则

模拟 MIPS O32 链接语义（`028` 版）：

| 类型 | 处理 |
|---|---|
| `R_MIPS_26`（jal/j） | `imm26 = ((S + A) >> 2) & 0x3FFFFFF`，A 从原指令 26 位还原 |
| `R_MIPS_HI16` | `hi = ((S + A + 0x8000) >> 16) & 0xFFFF` |
| `R_MIPS_LO16` | `lo = (S + A) & 0xFFFF`；HI16 与同符号的 LO16 成对处理，A 取自 LO16 指令立即数（符号扩展） |
| 孤儿 HI16 | 无配对 LO16 时单独写入高 16 位（A 取本指令立即数） |

### 2.1 符号地址来源（三步）

1. **本地符号**（`shndx == .text` 且有名字）：`0x100000 + st_value`
2. **undefined 符号**：名字自带地址（spimdisasm 命名惯例）
   - `FUN_00173658` → 0x173658
   - `D_0026FC40` → 0x26FC40
3. **段符号（名字为空）→ 从 asm 源码表达式恢复**：
   ee-as 2.10 会把 `%hi(D_001169C0)`（落在 .text 内的地址）优化成
   `section symbol + 0` 重定位，**addend 丢失**。解析器回读 `asm/1000.s` 对应行，
   用正则取出 `%hi(...)`/`%lo(...)` 内的表达式（`D_xxxx`、`FUN_xxxx + 0xN`），
   直接得到完整地址。
   → 这条路径**不再叠加指令 addend**（否则双计，本次曾出现 2 个 word 的 2 倍误差）。

## 3. 拼接器（tools/assemble_image.py）

按 `sections.json` 的 rom offset 把 10 个段贴回：

| 偏移 | 来源 | 大小 |
|---|---|---|
| 0x000000 | assets/0.bin（ELF header + phdr） | 4,096 |
| 0x001000 | build/splat/1000.resolved.bin | 1,124,764 |
| 0x11399C | assets/ctors.bin | 8 |
| 0x1139A4 | assets/dtors.bin | 8 |
| 0x1139AC | assets/reginfo.bin | 84 |
| 0x113A00 | assets/data.bin | 283,400 |
| 0x158D08 | assets/eh_frame.bin | 120 |
| 0x158D80 | assets/rodata.bin | 97,408 |
| 0x170A00 | assets/lit4.bin | 384 |
| 0x170B80 | assets/sdata.bin | 3,896 |

**边界说明（重要，别夸大）**：

- `.text` 是**真正从对象文件重建**的（汇编 + 重定位解析），这是本阶段的硬成果。
- 其余段目前是 **splat 拆出后原样贴回**（bin 段），不是从 C/数据定义重新生成。
  它们占游戏数据的大头（.data 283KB + .rodata 97KB），M1 允许这样；M4 再逐步重建。
- ELF 元数据（节头表、shstrtab、program headers）来自模板文件，属正常 —— 这些是链接器产物。

## 4. 复现

```bash
# 1) splat 拆分（已生成 asm/、assets/）
python -m splat split splat.yaml
# 2) 汇编（WSL 内，见 tools/fix_asm.py）
python3 tools/fix_asm.py /root/work/asm3 1000.s
# 3) 重定位解析（0 差异）
python tools/reloc_resolver.py
# 4) 拼接 + SHA
python tools/assemble_image.py
```

## 5. 独立验证（ee-ld）

并行调研结论：公开渠道**没有** SCE 原版 `ee-ld`（`ee-gcc2.96.tar.xz` 里只有 as）。
可用的替代：

| 方案 | 版本 | 说明 |
|---|---|---|
| **decompals/binutils-mips-ps2-decompals v0.10** | GNU ld 2.40 | 可直接链 ee-as 2.10 的 eabi64 对象；`-EL` 必须显式 |
| ps2dev 官方 v2.0.0 | GNU ld 2.45.1 | 需 `-m elf32lr5900`，253MB |

### 5.1 实测结果（本轮已完成）

已安装 `decompals/binutils-mips-ps2-decompals v0.10`（GNU ld 2.40）到 `/opt/ee-ld`，软链为 `/usr/local/bin/ee-ld`。

```bash
ee-ld -EL -G 8 --no-check-sections -Ttext 0x100000 -e _start $(cat defsym.args) -o 1000.elf out.o
```

- `defsym.args` 由 `tools/gen_defsym.py` 生成（spimdisasm 的 `D_00123456` 符号按名字里的地址喂给链接器）。
- splat 输出有 **93 处孤儿 `%hi`**（HI16 无配对 LO16），GNU ld 报 `can't find matching LO16 reloc`；
  `tools/literalize_hi.py` 把这 93 行改写成字面常量后链接通过。
- 链接产物 `.text` = **1,124,764 字节，与 baserom 0 差异**（`build/splat/1000.linked.text.bin`）。

**两条独立路径互证**：

| 路径 | 工具 | .text 差异 |
|---|---|---|
| 自研 reloc resolver | `tools/reloc_resolver.py` | 0 |
| 第三方链接器 | GNU ld 2.40（decompals） | 0 |
（见 `docs/splat-setup.md` §7 与 HANDOFF）。
