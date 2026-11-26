# M0 Spike 报告

> 执行日期：2026-11-26
> 判据：≥8/10 函数字节一致 → **11/11 通过**
> 结论一行：`11/11 matched, flags=-O2 -G0|-G8 (per TU), as=ee-as 2.10-ee-001003-1（与 2.9-ee-991111 产物一致）`

---

## 1. 结论

| 项 | 结果 |
|---|---|
| 匹配率 | **11/11**（7 个在 -G0 与 -G8 下都匹配；1 个仅 -G0；3 个仅 -G8） |
| 编译器 | SCE ee-gcc **2.96-ee-001003-1**（decompme/compilers 的 `ee-gcc2.96.tar.xz`，未 strip） |
| 汇编器 | `ee-as` **2.10-ee-001003-1**（随包）；另测 **2.9-ee-991111**，本批样本产物**逐字节相同** |
| flags | `-O2 -mips3 -c`；`-G` 值**按 TU 不同**：多数函数两者皆可，1 个需 -G0，3 个需 -G8 |
| 判定工具 | 自研 `tools/match_spike.py`（ELF32 解析 + 重定位感知字节比对）；objdiff-cli 3.8.3 已验证可运行，但单靠原始 ELF 无法给符号定位（见 §7） |
| 运行环境 | WSL2 Ubuntu（6.18 内核）+ `libc6:i386`（ee-gcc/ee-as 是 i386 Linux ELF） |

**M0 gate 通过 → 进入 M1-build。**

---

## 2. 匹配明细

所有结果均为与 `baserom/SLPM_665.70` 的 `.text`（文件偏移 `0x1000 + (addr-0x00100000)`）逐字节比较。

| 地址 | 大小 | 结果 | diff_words | 尝试 | 编译器 | flags |
|---|---|---|---|---|---|---|
| 0x00102078 | 8 | MATCH（G0/G8） | 0 | 1 | 2.96-ee-001003-1 | -O2 -mips3 -G0|-G8 |
| 0x00105FB0 | 8 | MATCH（G0/G8） | 0 | 1 | 同上 | 同上 |
| 0x001075D0 | 8 | MATCH（G0/G8） | 0 | 1 | 同上 | 同上 |
| 0x0010BB88 | 12 | MATCH（**-G0**） | 0 | 3 | 同上 | -O2 -mips3 -G0 |
| 0x0010C110 | 8 | MATCH（**-G8**） | 0（重定位感知） | 3 | 同上 | -O2 -mips3 -G8 |
| 0x00110598 | 20 | MATCH（G0/G8） | 0 | 1 | 同上 | 同上 |
| 0x00112588 | 12 | MATCH（G0/G8） | 0 | 4 | 同上 | 同上 |
| 0x00112AB8 | 12 | MATCH（G0/G8） | 0 | 3 | 同上 | 同上 |
| 0x00113480 | 12 | MATCH（**-G8**） | 0（重定位感知） | 3 | 同上 | -O2 -mips3 -G8 |
| 0x00123788 | 12 | MATCH（**-G8**） | 0（重定位感知） | 3 | 同上 | -O2 -mips3 -G8 |
| 0x0017F4E8 | 28 | MATCH（G0/G8） | 0 | 3 | 同上 | 同上 |

原始匹配记录：`build/spike/match_result.json`、`build/spike29/match_result.json`。
汇编后字节（`readelf -x .text` 口径，小端数值）：见各 `build/spike/*.G{0,8}.o`。

### 2.1 函数与源码形态

| 地址 | 原版指令 | 还原的 C |
|---|---|---|
| 0x00102078 | `jr $ra` / `move $v0,$zero` | `int f(void){return 0;}` |
| 0x00105FB0 | `jr $ra` / `andi $v0,$a0,0xffff` | `unsigned int f(unsigned short a){return a;}` |
| 0x001075D0 | `jr $ra` / `nop` | `void f(void){}` |
| 0x0010BB88 | `lui $v0,0x47` / `jr` / `addiu $v0,$v0,0x7d10` | `return (int)&g;`（**符号地址，非常量**；常量会编成 `ori`） |
| 0x0010C110 | `jr $ra` / `sw $a0,-0x6f30($gp)` | `void f(int x){ g = x; }`（**-G8 才产生 gp 相对单指令**） |
| 0x00110598 | `lw v1,0x48(a0)` / `lw v0,0x54(a0)` / `slt` / `jr` / `xori v0,v0,1` | `return s->x54 >= s->x48;` |
| 0x00112588 | `addiu $v0,$zero,1` / `jr` / `sw $v0,0xa8($a0)` | `void f(int *s){ s[0x2a] = 1; }`（**void 返回**；若声明 int 返回会多一条 `addiu`） |
| 0x00112AB8 | `sw $zero,0xc($a0)` / `jr` / `sw $zero,8($a0)` | `void f(int *s){ s[2]=0; s[3]=0; }`（源码顺序与延迟槽调度相反，需按原序写反） |
| 0x00113480 | `sw $zero,-0x7b1c($gp)` / `jr` / `sw $zero,-0x6d54($gp)` | `void f(void){ g1=0; g2=0; }`（-G8） |
| 0x00123788 | `lw $v0,-0x6d40($gp)` / `jr` / `sw $a0,8($v0)` | `void f(int x){ ((char*)p+8) = x; }`，p 为 -G8 小数据指针 |
| 0x0017F4E8 | 5 条 `sb`（0x17/0x18/0x15/0x16/0x14 顺序） | 5 个字节字段赋值，顺序照原序 |

源码在 `src/spike/*.c`（每个函数一个 TU，便于独立编译）。

---

## 3. 关键发现（对 M1 有直接影响）

### 3.1 `-G` 必须按 TU 标定，不能全局取一个值

- 7 个函数：`-G0` 与 `-G8` 产物相同（纯局部访问，不含小数据符号）。
- `0x0010BB88`：**只有 -G0 匹配**（`lui+addiu` 两条）；`-G8` 下该符号被当成 small data，变成 `addiu $v0,$gp,0` 一条 → 长度 12/12 但字节不同。
- `0x0010C110` / `0x00113480` / `0x00123788`：**只有 -G8 匹配**（`$gp` 相对单指令）；`-G0` 下变成 `lui+lw/sw`，长度 12→20 / 16 / 12→8 直接不符。

> 结论：M1 的 `configure.py` 必须支持 **per-TU `-G` 覆盖**；不能全工程写死 `-G0`。PLAN 里「SOTC 主程序 -O2 -G0、其 Loader 用 -G8」的说法在本作上得到印证，且比例可能更分散。

### 3.2 汇编器版本：2.9 与 2.10 在本批样本上无差异

HANDOFF/PLAN 要求「必须用 2.9-era `ee-as`，2.10 会缺 R5900 hazard nop」。实测：

- 11 个样本 × `-G0/-G8`：2.9-ee-991111 与 2.10-ee-001003-1 的 `.text` **逐字节相同**。
- 追加 `mult/div/mod` 三连测试：两者产物完全相同（1516 字节 .o，hex dump 一致）。

→ **本批未复现 hazard nop 差异**。可能原因：ee-gcc 2.96 的 .s 已自带调度 nop；或差异只在特定指令序列（如 `div.s` + 立即使用、`mult` 后紧跟 `mflo` 且无 nop 槽）出现。
**M1 行动项**：在大样本（≥200 函数，覆盖浮点 div、mult/mflo 链）上重跑 A/B；在此之前两版 as 都保留，默认用随包的 2.10。

### 3.3 源码形态陷阱（会直接导致不匹配）

1. **常量 vs 符号地址**：`return 0x477D10;` 编成 `lui+ori`；`return (int)&sym;` 才是 `lui+addiu` + 重定位。
2. **返回类型**：`0x00112588` 若声明 `int` 返回，gcc 会为返回值**再算一个常量**（多一条 `addiu`）；声明 `void` 才对。
3. **store 顺序**：延迟槽会吃掉最后一条 store，源码书写顺序需与「原版前序」相反才对齐（`0x00112AB8`）。
4. **指针类型别名**：`char*` 偏移 vs `int[]` 索引在部分函数会影响 CSE/调度。

### 3.4 重定位感知比对是必需的

3 个 `-G8` 函数在 `.o` 里是 `sw ...,0($gp)` + `R_MIPS_GPREL16`，原版是已解析的 `-0x6f30($gp)`。**必须做重定位感知比对**（mask 低 16 位 / 按符号解析），否则会被判成 diff。`tools/match_spike.py` 已实现「同 opcode+寄存器、仅立即数不同且该 word 有重定位」即判匹配。

---

## 4. 环境搭建（可复现）

```bash
# 1) WSL2 + Ubuntu（本机已装，装在 E:\wsl\Ubuntu）
wsl --install -d Ubuntu --location E:\wsl\Ubuntu --no-launch

# 2) i386 运行库（ee-gcc/ee-as 是 32 位 Linux ELF）
dpkg --add-architecture i386
apt-get update && apt-get install -y libc6:i386 libstdc++6:i386

# 3) 工具链
tar -xJf ee-gcc2.96.tar.xz -C /opt/ee        # bin/ee-gcc, bin/ee-as, lib/gcc-lib/ee/2.96-ee-001003-1/{cc1,cc1plus,cpp0}

# 4) 编译（注意：源文件必须放在 WSL 内部文件系统，不能在 /mnt/e 上编）
/opt/ee/bin/ee-gcc -O2 -G0 -mips3 -c x.c -o x.o
```

**坑 1：cc1 在 drvfs 上直接崩溃**
`/mnt/e`（drvfs）的 inode 值超出 32 位，2.96 的 `stat` 报 `Value too large for defined data type`，`cc1: Internal compiler error in init_c_lex`。
解法：把源文件拷到 `/tmp` 编译，再把 `.o` 拷回 Windows 侧。M1 的 Makefile 必须在 WSL 内做构建目录，不能直接在 `/mnt/e` 上编。

**坑 2：驱动硬编码 as 路径**
`ee-gcc -v` 显示 as 路径是 `/opt/ee/ee/bin/as`（相对 `-B` 前缀解析），**不读 PATH**。换汇编器只能替换该文件。

**坑 3：C 盘空间**
WSL 发行版默认装到 C 盘（`%LOCALAPPDATA%\wsl\{guid}\ext4.vhdx`），本机 C 盘只剩 3.5G → 装完直接 `ERROR_DISK_FULL`。必须 `wsl --install --location E:\...`（已如此处理）；C 盘 30M 时需 `wsl --unregister` 重装。

---

## 5. 数据与配置产出

| 文件 | 说明 |
|---|---|
| `config/symbols.csv` | 3,967 函数（address,size,name），来自 `IsPurePC/reports/all_functions/_index.tsv` |
| `config/symbol_addrs.txt` | 同数据，splat 风格 `name = 0x...; // type:func size:0x...` |
| `baserom/SLPM_665.70` | 原版 ELF，md5 `225d132fc85b7617ab7c49933a9d6e11`，1,514,848 字节 |
| `tools/pick_functions.py` | 叶函数筛选（size<64 / 无 jal,jalr / 无 COP1 / 无 .byte；**注意 disasm word 列是字节序拼接，需 byteswap**） |
| `tools/make_symbols.py` | `_index.tsv` → symbols.csv / symbol_addrs.txt |
| `tools/match_spike.py` | 字节比对（重定位感知），输出 `match_result.json` |
| `tools/dump_candidates.py` / `dump_diff.py` | 反汇编取证（capstone MIPS32 LE） |

### 5.1 筛选统计

- 全函数 3,967；size<64 且无调用/无浮点/无未识别字节的叶函数候选 **753** 个（8–63 字节）。
- 本次取 11 个（8–28 字节），覆盖：纯返回、参数截断、纯空函数、符号地址、gp 相对读写、结构体偏移比较、字节字段批量赋值。

---

## 6. 判据对照

| 判据 | 要求 | 实测 |
|---|---|---|
| 匹配率 | ≥8/10 | **11/11** |
| 编译器 | 2.96 真品 | ✔ 2.96-ee-001003-1 |
| flags | -O2 基本确定，-G 待标定 | -O2 确认；-G 确认**按 TU 混合** |
| 汇编器 | 2.9-era 待标定 | 2.9 与 2.10 本批一致；默认 2.10，M1 大样本复测 |

→ **通过。STATE.json 置 phase=M1-build。**

---

## 7. 未完成 / 遗留

1. **objdiff 未接入判定流**：`objdiff-cli 3.8.3` 可运行，但 `diff -1 SLPM_665.70 -2 x.o <symbol>` 报 `Symbol address out of section bounds` —— 原始 ELF 无符号表，objdiff 需要 splat 拆分出的带符号 target（`.o`/`.elf` + `symbol_addrs`）。**M1 建骨架时再接**；当前判定由 `match_spike.py` 承担。
2. **hazard nop A/B 未在大样本上复测**（见 §3.2）。
3. **-G 分布普查**：753 个叶函数里有多少需要 -G8、多少 -G0，是 M1 的关键数据。本次未做（只抽样 11 个）。
4. **浮点函数未覆盖**：本批刻意避开 COP1；M1 需验证 `div.s` 前 `nop;nop` 能否由 2.96+as 自动生成。
5. **未验证 `-O3`/`-Os` 等边界**：仅确认 `-O2`。

---

## 8. 命令存档（关键）

```bash
# 编译（WSL 内，源文件在 /tmp）
/opt/ee/bin/ee-gcc -O2 -G0 -mips3 -c src/00102078.c -o out/00102078.G0.o

# 判定（Windows 侧）
python tools/match_spike.py
SPIKE_DIR=spike29 python tools/match_spike.py

# 反汇编取证
python tools/dump_diff.py
```
