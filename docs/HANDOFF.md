# 交接：下一个会话从这里开始

## 当前进度

- 阶段：**M1 骨架（M0 spike 已通过，11/11）**
- 上一次更新：2026-11-26 13:40
- 下一阶段：**建骨架** — `configure.py` + splat + symbols + ld；`make check` 重建 .text 字节一致
- spike 报告：`docs/spike-report.md`

---

## 你的任务（一句话）

按 `docs/spike-report.md` §7 遗留项启动 M1 骨架；先做两件无争议的事：① 用 753 个叶函数做 **-G 分布普查**；② 把 `config/symbols.csv` 接进 splat，产出带符号的 target，让 objdiff 可用。

---

## 1. 先读

1. `docs/spike-report.md` — spike 结果、3 个源码形态陷阱、环境坑
2. `docs/PLAN.md` — 目标、选型、里程碑
3. `docs/STATE.json` — 当前阶段与 gate
4. 本文件 — 执行顺序

## 2. 环境（已就绪，勿重装）

```
WSL2 Ubuntu  E:\wsl\Ubuntu   (wsl -d Ubuntu -u root -- bash ...)
i386 libc    libc6:i386 已装
工具链       /opt/ee/bin/ee-gcc (2.96-ee-001003-1), /opt/ee/ee/bin/as (2.10-ee)
             /opt/ee29/ee/bin/as (2.9-ee-991111, A/B 用)
```

**硬约束：**

- 源文件必须放 WSL 内部（`/tmp` 或 `~/work`）编译；在 `/mnt/e` 上 cc1 会因 drvfs inode 溢出崩溃。
- `ee-gcc` 硬编码 as 路径 `/opt/ee/ee/bin/as`，不读 PATH。
- C 盘很紧（WSL 已装 E 盘）；别往 C 盘写大文件。

## 3. spike 已验证的事实（直接拿去用）

| 事实 | 数据 |
|---|---|
| 编译器 | ee-gcc 2.96-ee-001003-1 |
| flags | `-O2 -mips3 -c` |
| `-G` | **按 TU 混合**：11 个样本里 7 个无关、1 个需 -G0、3 个需 -G8 |
| 汇编器 | 2.10 与 2.9 在本批一致；默认 2.10，大样本再 A/B |
| 判定 | `tools/match_spike.py`（重定位感知字节比对） |
| 数据 | `config/symbols.csv` 3,967 行；`baserom/SLPM_665.70` md5 `225d132fc85b7617ab7c49933a9d6e11` |

## 4. M1 任务清单

1. **-G 分布普查**：对 753 个叶函数逐个编译 `-G0`/`-G8`，统计需要哪个；产出 `build/g-distribution.json`。这决定 `configure.py` 的默认值。
2. **splat 接入**：用 `config/symbol_addrs.txt` 拆 `.text`；产出带符号的 target object，使 `objdiff-cli diff` 可用（当前报 `Symbol address out of section bounds`）。
3. **configure.py**：per-TU `-G` 覆盖 + `-O2 -mips3` + WSL 内构建目录。
4. **make check**：整段 `.text` 重建后与 baserom 逐字节一致（先做仅含未匹配原字节的骨架）。
5. 浮点样本：验证 `div.s` 前 `nop;nop` 能否由 2.96+as 自动生成（本 spike 未覆盖 COP1）。

## 5. 数据准备（从旧项目取，不改旧项目）

| 文件 | 源路径 | 用途 |
|---|---|---|
| 函数表 | `E:\ONE PIECE\S\IsPurePC\reports\all_functions\_index.tsv` | 已转 `config/symbols.csv` |
| 调用图 | `...\artifacts\data\analysis\functions.json` | 叶函数筛选（2,792 条调用图记录，少于 3,967） |
| 反汇编 | `...\artifacts\data\analysis\disasm_text.txt` | 证据卡；**word 列是字节序拼接，取 opcode 需 byteswap** |
| 段表 | `...\artifacts\data\analysis\sections.json` | ld 脚本（.text 0x00100000/off 0x1000, .lit4, .reginfo） |
| 原版 ELF | `...\artifacts\data\samples\SLPM_665.70` | 已在 `baserom/`（gitignore） |

## 6. 匹配循环（沿用）

1. 从 `disasm_text.txt` 切出 `[start, end)` 指令
2. 写 `.c`（含 `// FUNCTION: SLPM <addr>` 标注）
3. 编译：`ee-gcc -O2 -mips3 -c`，`-G0` 与 `-G8` 各一次
4. `python tools/match_spike.py`（或后续 objdiff）
5. 不中 → 先查三个陷阱：**常量vs符号地址 / 返回类型 / store 顺序**，再改假设
6. 记录进 `progress/ledger.tsv`

## 7. 判据（M1）

| 结果 | 动作 |
|---|---|
| `make check` 整段 .text 字节一致 | 进入 M2 自动化 |
| 仅部分段一致 | 修 ld 脚本与 `-G` 分布，最多两周 |
| 无法重建 | 写 `docs/m1-failed.md`，保留命令与 diff，交回决策 |

## 8. 回写（必须做）

1. 更新 `docs/STATE.json`（phase、next_action、updated、notes）
2. 更新本文件顶部「当前进度」
3. 新匹配函数进 `src/` 并记入 `progress/ledger.tsv`
