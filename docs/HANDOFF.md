# 交接：下一个会话从这里开始

## 当前进度

- 阶段：**M2.1 完成**（per-function override）
- 上一次更新：2026-11-26 13:48
- 验收：`make check` 一条命令 → **SHA-256 = `e0d0b77b555fd876c6fdd933b486292da45e77677b44bc04eec67836de481147` = 原版**（其中 5 个函数 / 104 字节已改由 C 提供）
- 下一步：**M2.2 triage 队列**（`tools/triage.py` + `build/queue.json` + 认领）→ match_kit → ledger 自动化

---

## 你的任务（一句话）

M1 已收口，M2.1 已完成：`build.py` 支持 per-function override，5 个 local 函数已走通「写 C → 编译 → 重定位 → 逐字节比对 → 覆盖 .text」，`make check` 仍 SHA 一致。下一步是 M2.2 triage 队列。

---

## 1. 先读

1. `docs/build.md` — **一条命令构建与验收**（本轮新增）
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

1. `tools/triage.py`：按 size/叶函数/FPU/gp 给函数分难度队列
2. 队列文件 `build/queue.json` + 认领（参考 rac4 的 `claims.py` 思路）
3. `tools/match_kit.py`：编译 + objdiff + 结果归档一条命令
4. `progress/ledger.tsv` 自动追加
5. 无人值守跑通 50 个函数

## 7. 判据（M2）

| 结果 | 动作 |
|---|---|
| 无人值守跑完 50 函数 | 进 M3 批量 |
| 匹配率 <50% | 检查 objdiff 工程配置与符号名对齐 |

## 8. 回写（必须做）

1. `docs/STATE.json`（phase、next_action、gates、notes）
2. 本文件顶部「当前进度」
3. 新匹配函数进 `src/` + `progress/ledger.tsv`
