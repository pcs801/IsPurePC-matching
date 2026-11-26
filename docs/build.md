# 构建与验收（M1）

> 一条命令：`python tools/build.py check`（有 make 时 `make check`）
> 验收标准：重建镜像 SHA-256 等于原版 `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147`

---

## 1. 命令

```bash
# 完整链路 + 验收（splat -> asm -> resolve -> image -> sha256）
python tools/build.py check

# 跳过 splat（复用 asm/，快 1 分钟左右）
python tools/build.py check --fast

# 只构建不验收
python tools/build.py build

# 额外：用 GNU ld 独立验证 .text（见 docs/m1-image.md §5.1）
python tools/build.py ld

# 重新生成 per-TU -G 配置
python tools/build.py configure

# 只编译 + 逐字节校验逐函数 C 覆盖（不重建镜像，约 5 秒）
python tools/build.py overrides
```

本机已通过 MSYS2 安装 GNU Make（`pacman -S make`，make 4.4.1，位于 `C:\msys64\usr\bin\make.exe`）。
若 PATH 里没有，直接用完整路径：`C:\msys64\usr\bin\make check`。等价命令：

```bash
make check      # = python tools/build.py check
```

其他环境等价：

```bash
make check      # = python tools/build.py check
make build
make ld
make configure
```

## 2. 链路

| 步骤 | 动作 | 位置 |
|---|---|---|
| 1/6 | `splat split splat.yaml` → `asm/1000.s` + `assets/*.bin` | Windows Python |
| 2/6 | WSL 内 `tools/fix_asm.py` 汇编 → `build/splat/1000.o` | WSL `/root/work/build` |
| 3/6 | `tools/reloc_resolver.py` 解析 15,560 条重定位 → `1000.resolved.bin` | Windows Python |
| 4/6 | `config/overrides.json` 的 C 覆盖：WSL 编译 → 重定位解析 → 逐字节比对 → 覆盖 .text | WSL + Windows Python |
| 5/6 | `tools/assemble_image.py` 10 段拼接 → `SLPM_665.70.rebuilt` | Windows Python |
| 6/6 | SHA-256 比对 baserom | Windows Python |

耗时（本机实测，含 splat）：约 **2–3 分钟**；`--fast` 约 1–1.5 分钟。

## 3. configure.py（per-TU `-G`）

读 `build/g-distribution.csv`（来自 `tools/g_distribution.py` 的静态普查），产出：

| 文件 | 内容 |
|---|---|
| `config/build_config.json` | 工具链路径、base flags、每个函数的 `-G` 建议（`8` / `0` / `try-both` / `either`） |
| `config/tu_g.json` | 把 needs_G8 函数按「间距 ≤ 0x2000」聚成 **6 个地址区间**，其余默认 `-G0` |

当前分布（3,967 函数）：

```
needs_G8: 727   ambiguous: 1,714   local: 1,526
> -G8 区间覆盖 557,404 字节（最大 0x104DA8-0x16EAAC，641 个函数）
```

用途：以后写 C 匹配时，按函数地址查 `g_map`：

- `needs_G8` → 直接用 `-G8` 编译
- `local` → 与 `-G` 无关（66% 的候选），可批量
- `ambiguous` / `try-both` → `-G0` 与 `-G8` 各试一次

## 4. per-function override（M2.1）

已匹配的函数不再由 splat 的汇编提供字节，而是由 `src/` 的 C 编译出来。登记表：

```
config/overrides.json    # { addr, size, name, source, g, status, note }
```

| status | 行为 |
|---|---|
| `matched` | 编译 + 重定位后**必须**与 baserom 对应地址逐字节相等，字节覆盖进 `1000.resolved.bin`；不等则整条构建失败 |
| `todo` | 只编译用于诊断（`make overrides` 会提示已命中的 todo），不覆盖、不影响 `make check` |

实现要点（`tools/build.py`）：

- 编译：源文件先拷进 WSL `/root/work/overrides` 再 `ee-gcc -O2 -mips3 -G<n> -c`（不能在 `/mnt/e` 上编，drvfs 会让 2.96 cc1 崩）。
- 重定位：与 `tools/reloc_resolver.py` 同一套符号规则解析 `R_MIPS_26 / HI16 / LO16 / GPREL16`（gp = `0x002779F0`），所以 `jal`、`%hi/%lo`、`$gp` 相对访问也能判等，不是「同 opcode 不同立即数」的假匹配。
- 比对失败会打印逐 word 差异（compiled vs baserom）。**任何 `matched` 条目不相等，`make check` 直接失败**，不会静默通过。
- 验收段会打印覆盖统计：`overrides: N function(s), M bytes of .text came from C sources`。

当前覆盖 5 个函数（都是 class=local，-G0），共 **104 字节**：

```
0x00155B68 12  FUN_00155b68  两个 int store，第二条填延迟槽
0x00177C28 12  FUN_00177c28  0x168/0x16c 清零，调度器把两条 store 顺序反转
0x0019B590 28  FUN_0019b590  两个字段 ×2（lw/lw/sll/sll/sw/sw）
0x001A8208 28  FUN_001a8208  a<<12 存两处；5 条独立 store 的源序由 120 种排列搜索确定
0x001A82A8 24  FUN_001a82a8  (p[0]>>12) == p[2]（sra+xor+sltiu）
```


## 5. 环境前置

```
WSL2 Ubuntu  E:\wsl\Ubuntu
/opt/ee          ee-gcc 2.96 + ee-as 2.10
/opt/ee-ld       GNU ld 2.40（decompals），/usr/local/bin/ee-ld
Windows Python   splat 0.50.1 + spimdisasm 1.42.4
```

**注意**：汇编必须在 WSL 内（`/root/work`），不能在 `/mnt/e`（drvfs 会让 2.96 cc1 崩）；
`/tmp` 会在 WSL 重启后清空，不要用。

## 6. 验收含义

SHA 相等说明：**10 个段拼回去的 ELF 与原版逐字节一致**。

诚实边界（见 `docs/m1-image.md`）：

- `.text` 是真正重建的（splat 反汇编 → ee-as 汇编 → 重定位解析），**0 差异**；
- `.data/.rodata/.lit4/.sdata` 是 splat 拆出后原样贴回，不是从数据定义重生成；
- ELF 元数据（header/phdr/shdr/shstrtab）取模板文件。

有 C 覆盖时，SHA 相等还额外证明了这几段函数的 C 编译产物逐字节正确（见 §4）。

所以这条 gate 证明的是「**.text 可字节级重建 + 段布局正确**」，不是「全部游戏数据已重新生成」。
