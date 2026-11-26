# M2.2 — triage 队列 + 50 个 easy 函数无人值守批次

> 项目：IsPurePC-Matching（PS2 SLPM-66570）
> 日期：2026-11-26 19:33
> 结论：**50 个 easy 函数无人值守跑完，40 个 MATCH（80%）**；平均尝试 **1.72** 次（命中函数 1.25 次）。
> 验收：`python tools/build.py overrides` → **45/45 MATCH**；`make check` → **RESULT: MATCH**（SHA 不变，45 函数 / 656 字节来自 C）。

---

## 1. 本轮做了什么

| # | 动作 | 产物 |
|---|---|---|
| 1 | 全量函数分档（size / 叶函数 / 分支 / FPU / 填充 / 标量整数） | `tools/triage.py` → `build/queue.json` |
| 2 | 原子认领 + 租约（参考 rac4 的 claims 思路，本地实现） | `tools/claims.py` → `build/claims.json` |
| 3 | 批量编译 + 重定位感知逐字节比对 | `tools/match_kit.py` |
| 4 | 认领 → 从汇编生成 C 候选 → 比对 → 回写的批次循环 | `tools/auto_match.py` |
| 5 | 无人值守跑 50 个 easy 函数（5 批 × 10，`make progress` 每批后执行） | `build/m2-2-results.json`、40 个 `src/functions/*.c` |
| 6 | 本报告 | `docs/m2-2-batch.md` |

复现命令：

```bash
python tools/triage.py                      # 重建 build/queue.json
python tools/claims.py stats                # 队列/认领概览
python tools/auto_match.py --owner m22-worker --tier easy --limit 50 \
       --batch-size 10 --sample systematic  # 认领 + 生成 + 编译 + 比对 + 回写（每批后 make progress）
python tools/build.py overrides             # 45 个 matched 覆盖逐字节复核（约 15 秒）
make check                                  # 整镜像 SHA 验收（2–3 分钟）
```

---

## 2. triage：分档策略与队列

`tools/triage.py` 读 `config/symbols.csv`（3,966 个函数）、`asm/1000.s`（281,191 条指令）、`config/build_config.json`（per-function `-G`），产出 `build/queue.json`。

### 2.1 分档规则

| 档位 | 条件 |
|---|---|
| **easy** | 叶函数（无 call/尾跳）、无分支、无 FPU、无 syscall、纯标量整数、**core 4–64 字节**、`size == core`（无尾部对齐填充）、单一返回点 |
| **medium** | 叶函数 + 标量整数 + core ≤ 160（允许填充，但打 `padding` 标签）；或带分支的小函数 |
| **hard** | 其余（调用、FPU、syscall、非标量指令、多返回点、体积过大） |

### 2.2 队列统计

```
总函数 3,966
easy    139   尺寸: 8B:68  16B:26  24B:17  32B:8  40B:12  48B:4  56B:3  64B:1（其中 28 个含 gp 访问）
medium  195   其中 157 个带对齐填充
hard  3,632   其中 1,398 个带对齐填充
```

**为什么把填充函数踢出 easy**：`build.py` 的覆盖逻辑要求 `len(compiled .text) == symbol size`。baserom 里部分函数尾部有 4 字节对齐 `nop`，C 编译器无法产生这些字节，所以带填充的函数在当前 gate 下**不可能**字节全等。它们被降为 medium（`flags: ["padding"]`），不静默丢弃。

**multi-return**：若同一符号内出现 2 个及以上 `jr $ra`（多个返回点），按 hard 处理，避免线性翻译出错误代码。

队列条目字段：`addr/size/core/name/cls/g/tier/score/ins/leaf/straight/fpu/syscall/gp/calls/branches/unsupported/flags/sig/reason/rank`。排序：`(tier, score, addr)`，score = core + 50×padding + 200×branch + 400×calls + 25×unsupported 数。

---

## 3. claims：原子认领与租约

`tools/claims.py` 把 `build/queue.json` 当作只读工作单，把 `build/claims.json` 当作可变台账：

- **互斥**：所有写操作在 `build/.claims.lock` 上用 `O_CREAT|O_EXCL` 抢锁（30 秒超时，>120 秒视为陈旧锁自动清理），两个 worker 不可能拿到同一个函数。
- **租约**：claim 默认 1,800 秒；进程死掉后租约过期，函数可被其他 worker 重新认领，旧记录进 `history`。
- **命令**：`claim-next / claim / release / complete / status / stats / check / reset`。
- **结果**：`MATCH / MISS / UNSUPPORTED / ERROR`，附带 `attempts`、`note`、`source`。

本轮 50 次认领、0 次重试、0 个租约冲突（`build/claims.json`：`next_seq=51`，`history=[]`）。

> rac4 的 `claims.py` 不在本机，按其「原子认领 + 时间锁 + 断言」思路做了本地等价实现，未抄其 ProDG 相关部分。

---

## 4. match_kit + auto_match

### 4.1 match_kit（编译/比对原语）

- 一批候选源码写进 `build/candidates/<tag>/`，**一次 WSL 调用**全部 `ee-gcc -O2 -mips3 -G<n> -c`（在 `/root/work` 内编译，避免 drvfs 崩 2.96 cc1）。
- 每个 `.o` 的 `.text` 用 `tools/build.py` 同一套重定位规则解析（`R_MIPS_26/HI16/LO16/GPREL16/32`，gp = `0x002779F0`），再与 baserom 对应地址逐字比对。
- 返回长度、逐 word 差异、未解析重定位；编译错误 `.err` 会拷回候选目录，便于诊断。

### 4.2 auto_match（生成器）

从 splat 反汇编做寄存器级符号执行：`lui/addiu/ori/andi/xori`、`addu/daddu/subu`、`sll/srl/sra(+32)`、`slt(i)(u)`、`mult/div/mflo`、`movn/movz`、`lb/lbu/lh/lhu/lw/lwu/ld` 与对应 store、`jr $ra`。地址表达式归一到「符号/参数 + 常量偏移 + 索引」形式，识别三类基址：

1. 参数指针（按访问宽度/符号性声明 `int* / unsigned char* / ...`）；
2. 全局符号（`%hi/%lo(SYM)` 合并为一个符号；`$gp±off` 折成绝对地址 `D_XXXXXXXX`，自动生成 `extern` 声明）；
3. 全局指针（先从符号 `lw` 再解引用，声明为 `extern T *SYM`）。

每个函数最多生成 24 个候选：自然类型 / unsigned / char* 强转 × 返回类型（int/unsigned/long long/void）× 语句顺序（≤4 条 store 时优先尝试置换）× 队列给的 `-G`（local→0，needs_G8→8，ambiguous→0/8 都试）。分两波编译：前 6 个先试，未中再试剩余。**只在逐字节全等时落盘**。

### 4.3 抽样

`--sample systematic`：在 easy 档 139 个函数（按难度排序）上等距取 50 个，尺寸分布覆盖 8–56B，避免只跑最小的 8B 函数。实测样本按尺寸：

| 尺寸 | 8B | 16B | 24B | 32B | 40B | 48B | 56B |
|---|---|---|---|---|---|---|---|
| 样本数 | 24 | 10 | 6 | 3 | 4 | 2 | 1 |

---

## 5. 结果

### 5.1 总体

| 指标 | 数值 |
|---|---|
| 函数数 | **50** |
| MATCH | **40（80.0%）** |
| MISS | 10 |
| UNSUPPORTED | 0 |
| 平均尝试次数（全体） | **1.72**（86 次尝试 / 50 函数） |
| 平均尝试次数（命中者） | **1.25** |
| 新增 C 覆盖 | 40 函数 / **552 字节** |
| overrides 总数 | 45 matched（原 5 + 本轮 40） |
| 独立复核 | `build.py overrides`：**45/45 MATCH** |
| 整镜像 gate | `make check`：**RESULT: MATCH**，SHA 未变；45 函数 / 656 字节来自 C |

`make progress` 每批后执行，5 次 `HTTP=201` 上传（ByteMatch 项目 `pcs801/IsPurePC-matching`）。

### 5.2 逐批

| 批 | 认领 | MATCH | 累计 | 批耗时 |
|---|---|---|---|---|
| 1 | 10 | 10 | 10/50 | 7.7s |
| 2 | 10 | 10 | 20/50 | 8.9s |
| 3 | 10 | 10 | 30/50 | 8.4s |
| 4 | 10 | 8 | 38/50 | 6.1s |
| 5 | 10 | 2 | 40/50 | 6.8s |

### 5.3 按尺寸（难度梯度非常明显）

| core | MATCH/样本 | 命中率 |
|---|---|---|
| 8B | 24/24 | 100% |
| 16B | 9/10 | 90% |
| 24B | 5/6 | 83% |
| 32B | 0/3 | 0% |
| 40B | 1/4 | 25% |
| 48B | 0/2 | 0% |
| 56B | 1/1 | 100% |

### 5.4 尝试次数分布

| 尝试 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|
| 函数数 | 37 | 4 | 2 | 3 | 2 | 1 | 1 |

> 尝试次数 = 为命中该函数实际编译并比对的候选数；MISS 记为试完全部候选。37/50 一次命中，说明「自然类型 + 程序顺序 + 队列给的 -G」这条首选路线对 easy 档足够。

### 5.5 -G 与分类

- 命中函数：`-G0` 33 个、`-G8` 7 个。
- 分类：`local` 27/32、`needs_G8` 7/10、`ambiguous` 6/8。

### 5.6 10 个 MISS 的诊断

| 地址 | 尺寸 | 签名 | 诊断 |
|---|---|---|---|
| 0x001C2A78 | 16 | `lwu; dsll32; jr; dsra32` | 64 位符号扩展惯用式；gcc 2.96 对等价 C 选择了 `jr + lw` 延迟槽形态（8B），与原 16B 不同 |
| 0x001C0E40 | 32 | `lw; lui; dsrl32; dsll; and; dsll32; jr; dsra32` | 同上，64 位位运算 + 调度差异 |
| 0x0017ACA0 | 24 | `daddu; sll; addu; lw; jr; addu` | addu 操作数顺序/寄存器分配不同（`a1+a0` vs `a0+a1`） |
| 0x00123968 | 40 | `lw; lw; sll; addu; sll; subu; sll; addu; jr; sw` | 复杂数组索引，寄存器分配不同 |
| 0x0012B628 | 48 | `sll; lw; addu; sll; lui; ori; addu; addu; daddu; sw; jr; sw` | 地址算术 + 常量折叠顺序不同 |
| 0x001D58A8 | 48 | `sll; sll; addu; lui; addu; lw; sll; lui; addiu; addu; jr; sw` | 同上（已可编译，仍差 13 word） |
| 0x00105818 | 32 | `lui; sll; addu; lw; sll; addu; jr; lhu` | 全局常量加载被提前/重排（word0 不同） |
| 0x001F7170 | 32 | `... mult; mflo; subu ...` | 乘除取模的代码生成形态不同（40B vs 32B） |
| 0x0012D350 | 40 | `lw; addiu; lui; addu; lb; slti; slti; xori; jr; movn` | `movn` 选择式与操作数顺序 |
| 0x001E02D8 | 40 | `... movz ... jr; movz` | 同上（movz） |

归类：64 位惯用式 2 个、地址/调度/寄存器分配 4 个、数组索引 2 个、movn/movz 2 个。全部是**同一 C 语义下 gcc 2.96 选了不同指令序列**，不是语义错误。

---

## 6. 诚实边界

1. **只跑了 easy 档**：medium 195（含 157 个填充函数）、hard 3,632 未动。80% 只代表 easy 档，不能外推到全项目。
2. **只支持标量直线叶函数**：带分支、调用、FPU、syscall、非标量指令（packed/128-bit/非对齐）的函数生成器直接判 UNSUPPORTED（本轮 0 个，因为 triage 已排除）。
3. **填充问题**：157 个 medium 函数尾部有对齐 `nop`，当前 gate 下无法由 C 生成；需要单独决定「允许声明 core 尺寸」或「C 覆盖允许尾部 nop 差异」，本轮没有放宽 gate。
4. **尝试次数口径**：按编译并比对的候选数计；MISS = 试完全部候选。不是因为搜索空间大，而是变体维度有限。
5. **生成的 C 是机器生成**：普通 C（无 inline asm / .word / volatile / goto），可读性一般，但不含 CHEAT；每个文件头有地址与签名。
6. **objdiff 仍未接入**：本轮用「重定位感知的逐字节比对」代替 objdiff；`match_kit` 已把编译/比对抽成原语，后续可直接接 objdiff-cli。

---

## 7. 产物清单

| 路径 | 说明 |
|---|---|
| `tools/triage.py` | 分档 → queue |
| `build/queue.json` | 3,966 函数队列（tier/score/rank/g/flags） |
| `tools/claims.py` | 原子认领/租约台账 |
| `build/claims.json` | 50 条认领记录（0 重试） |
| `tools/match_kit.py` | 批量编译 + 重定位感知比对 |
| `tools/auto_match.py` | 候选生成 + 批次循环 + 回写（含 `--clean`） |
| `build/m2-2-results.json` | 50 函数逐条结果、逐批统计、汇总 |
| `build/m2-2-run.log` / `build/m2-2-check.log` | 运行/验收日志 |
| `src/functions/*.c` | 新增 40 个匹配函数（目录里另有原 5 个 matched 与 1 个 REJECTED 实验 00112bf8.c） |
| `config/overrides.json` | 45 条 matched |
| `progress/ledger.tsv` | 追加 40 行 |
| `docs/progress.html`、上传的 report | `make progress` 产物 |

---

## 8. 下一步（M2.3）

1. **medium 档**：先定 padding 策略（`size=core` 声明 or 允许尾部 nop），再跑 50–100 个。
2. **生成器补强**（按本轮 MISS 频率）：64 位惯用式、`movn/movz`、复杂数组索引的寄存器分配、语句顺序搜索扩展（>4 store 的排列/部分序）。
3. **match_kit 接 objdiff-cli**：保留字节 gate，同时给出指令级 diff 视图。
4. **多 worker**：claims 已支持租约，可并行 2–4 个进程（不同 `--owner`），共享 `build/claims.json`。
5. **ledger 自动化**：把「证据卡（asm 摘要 + 候选数 + 差异）」写进 `progress/` 每次命中。
