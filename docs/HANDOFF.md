# 交接：下一个会话从这里开始

## 当前进度

- 阶段：**M2.2 完成**（triage 队列 + 50 函数无人值守批次）
- 上一次更新：2026-11-26 19:40
- 验收：`make check` → **SHA-256 = `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147` = 原版**（其中 **45 个函数 / 656 字节**已改由 C 提供）
- M2.2 批次：50 个 easy 函数 → **40 MATCH（80%）**，平均尝试 **1.72** 次（命中 1.25），详见 `docs/m2-2-batch.md`
- 下一步：**M2.3** medium 档（先定 padding 策略）+ 生成器补 64 位/movn/movz + match_kit 接 objdiff

---

## 你的任务（一句话）

M1/M2.1 已收口，M2.2 已完成：`triage.py`（3,966 函数分档）+ `claims.py`（原子认领/租约）+ `match_kit.py`（批量编译 + 重定位感知比对）+ `auto_match.py`（汇编→C 候选）跑通 50 个 easy 函数，40 命中，`make check` 仍 SHA 一致。下一步是 M2.3 medium 档。

---

## 1. 先读

0. `docs/m2-2-batch.md` — **M2.2 批次报告**（分档/认领/生成器/50 函数结果/诚实边界）
1. `docs/build.md` — **一条命令构建与验收**
2. `docs/m1-image.md` — reloc resolver 规则、段拼接、双验证、诚实边界
3. `docs/splat-setup.md` — splat 的 4 个坑
4. `docs/g-distribution.md` — per-TU `-G` 普查
5. `docs/STATE.json` — gate 全绿

## 2. 构建（M1 已固化）

```bash
python tools/build.py check     # splat -> asm -> resolve -> overrides -> image -> sha256
python tools/build.py check --fast   # 跳过 splat
python tools/build.py ld        # 额外：GNU ld 独立验证 .text
python tools/build.py configure # 重生成 per-TU -G 配置
python tools/build.py overrides # 只编译+校验 config/overrides.json（约 5 秒）
```

**必须看到**：`RESULT: MATCH`。耗时约 2–3 分钟。

## 3. 环境（已就绪）

```
WSL2 Ubuntu  E:\wsl\Ubuntu
/opt/ee/bin/ee-gcc 2.96-ee-001003-1     /opt/ee/ee/bin/as 2.10-ee
/opt/ee-ld/bin/mips-ps2-decompals-ld (GNU ld 2.40)   /usr/local/bin/ee-ld
Windows Python 3.10: splat 0.50.1 + spimdisasm 1.42.4
objdiff: toolchain/dl/objdiff-cli.exe
```

硬约束：汇编在 WSL 的 `/root/work`；`/mnt/e` 会让 2.96 cc1/ld 崩；`/tmp` 重启即清空。

## 4. 事实速查

| 项 | 值 |
|---|---|
| 编译器 | ee-gcc 2.96-ee-001003-1，`-O2 -mips3` |
| per-TU -G | 6 个 needs_G8 区间（覆盖 557KB），默认 -G0；见 `config/tu_g.json` |
| 函数分布 | needs_G8 727 / ambiguous 1,714 / local 1,526（候选 761 里 76/181/504） |
| gp | 0x002779F0 |
| .text 重建 | 0 差异（resolver 与 GNU ld 双证） |
| 整镜像 | SHA 一致 |
| 符号 | `config/symbol_addrs.txt` 3,966 个 |
| C 覆盖 | 5 个 local 函数 / 104 字节 / `config/overrides.json` |

## 5. 匹配循环（M2 起点）

1. 从 `asm/1000.s` 或 `disasm_text.txt` 取函数
2. 查 `config/build_config.json` 的 `g_map` 决定 `-G0`/`-G8`
3. 写 C（`// FUNCTION: SLPM <addr>`，函数名 `FUN_<addr>` 对齐 splat）
4. 在 `config/overrides.json` 登记 `{addr,size,source,g,status:"todo"}`，`make overrides` 编译+逐字节比对（重定位感知）
5. 不中先查：**常量vs符号地址 / 返回类型 / store 顺序 / 是否有 reload（volatile 类）**
6. 命中后把 status 改成 `matched`，`make check` 确认 SHA 仍一致，记 `progress/ledger.tsv`

## 6. M2 清单

1. ✅ `tools/triage.py`：size/叶函数/分支/FPU/padding/gp → easy 139 / medium 195 / hard 3,632
2. ✅ `build/queue.json` + `tools/claims.py`（原子认领 + 租约，本地版 rac4 思路）
3. 🟡 `tools/match_kit.py`：批量编译 + 重定位感知逐字节比对已可用；objdiff-cli 还没接
4. ✅ `auto_match.py` 命中时自动追加 `progress/ledger.tsv`（证据卡仍待做）
5. ✅ 无人值守跑通 50 个 easy 函数 → 40 MATCH

## 7. 判据（M2）

| 结果 | 动作 |
|---|---|
| 无人值守跑完 50 函数 | 进 M3 批量 |
| 匹配率 <50% | 检查 objdiff 工程配置与符号名对齐 |

## 8. 回写（必须做）

1. `docs/STATE.json`（phase、next_action、gates、notes）
2. 本文件顶部「当前进度」
3. 新匹配函数进 `src/` + `progress/ledger.tsv`
