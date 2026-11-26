# IsPurePC-Matching — 计划

> 目标：把 PS2《I's Pure》(SLPM-66570, 2006, Regista / Takara Tomy) 按字节级 matching decompilation 还原为可编译的 C 源码。
> 判定：每个函数的编译字节与原版相等（objdiff）；未匹配函数用原版字节补齐。
> 完成线：函数级 ≥95%，行为 100%（原字节补齐）。
> 建立：2026-11-26。旧项目 `E:\ONE PIECE\S\IsPurePC` 暂停，仅作资产源。

---

## 1. 决策记录

- **2026-11-26**：放弃“行为移植 + matching 双轨”，转为 **matching 单轨**。
- 旧项目不删除、不继续开发；其 `src/`、`include/` 仅作语义参考，**不参与匹配构建**。
- 新项目独立目录，不复用旧构建系统与验证体系。

---

## 2. 编译器事实（实测，勿改）

| 项 | 证据 |
|---|---|
| 编译器 | SCE ee-gcc **2.96**（二进制含 `Append: GCC2096 SCE3100`） |
| 栈保存步长 | `sd` 8 字节（179 次 / 16 字节仅 4 次）→ 排除 1999 年的 2.9-ee-991111 |
| `div.s` 前 `nop;nop` | 97/97 = 100% → SCE 补丁特征，排除 CodeWarrior |
| ProDG / CodeWarrior | `sq` = 0、无 `.comment` → 排除 |
| 浮点常量形态 | `mtc1` 1,126 次，43% 由 `lui/li` 直喂；`.lit4` 仅 0x170 → 2.96 风格（3.x 会大量走 `.rodata`） |
| 段布局 | `.text` 0x11299c、`.lit4`、`.mdebug.eabi64`(0)、`.reginfo`、`.sdata/.sbss` |
| 汇编器 | 必须用 **2.9-era `ee-as`**（R5900 hazard nop 的来源），版本待 spike 标定 |
| flags | `-O2` 基本确定；`-G0/-G8` 待标定（SOTC 主程序 `-O2 -G0`，其 Loader 用 `-G8`） |

> 参数来源：`decompme/compilers` 的 `ee-gcc2.96.tar.xz`（真品，未 strip）；2.9-era `ee-as` 随包或从同代 SCE 套件取。

---

## 3. 规模

| 项 | 数值 | 来源 |
|---|---|---|
| 函数数 | **3,967** | `IsPurePC/reports/all_functions/_index.tsv` |
| `.text` | 1,124,764 字节（0x11299c） | 段表实测 |
| 指令数 | 257,029 | `disasm_text.txt` |
| SDK 库（免移植） | 188,732 字节（18.4%） | 旧项目评估 |
| 需匹配函数 | 约 3,200 | 扣 SDK 后估算 |

---

## 4. 路线选型

| 层 | 来源 | 理由 |
|---|---|---|
| 项目骨架 | **SOTC**（`TheRealestNwah/sotc-decomp`） | 同编译器 ee-gcc 2.96、`-O2 -G0`、长期目标是 PC 原生移植、`CLAUDE.md` 有 autonomous work 定义 |
| 工具与方法 | **decomp-compat-kit** | `fingerprint_elf / triage / match_kit / verify_decomp / ledger` + tier 角色 + CHEAT lint + MCP |
| 零件 | **rac4-decomp** | `tools/claims.py` 原子认领、批量提交规则（10+ 函数一 commit） |

**明确不抄：**

- rac4 的 ProDG 工具链与 `-fopt-stack`（SCE 编译器无此 flag，抄了编译不过）
- ra2 的 VC6 / `check.py` / reccmp 流程（x86 专用）
- xsg-i 的 `config/symbols`（那是 Xenosaga 的数据）

---

## 5. 里程碑

| 阶段 | 时间 | 内容 | 通过判据 |
|---|---|---|---|
| **M0 spike** | 2026-11-27 ~ 12-10 | 装 ee-gcc 2.96 + 2.9-era ee-as + objdiff；转 symbols；10 个最短叶函数匹配 | ≥8/10 字节一致 |
| **M1 骨架** | +2 周 | `configure.py` + splat + symbols + ld；`make check` 能重建原版段 | 整段字节一致 |
| **M2 自动化** | +2 周 | triage + 队列 + match_kit + ledger + 报告 | 无人值守跑完 50 函数 |
| **M3 90%** | 3–5 个月 | easy/medium 批量 | 匹配率 ≥90% |
| **M4 95% + 收尾** | 弹性 | hard 归档、原字节补齐、整链校验 | ≥95%，`check` 通过 |

---

## 6. 完成定义

1. 函数级匹配率 **≥95%**（按字节统计）。
2. 未匹配函数保留原字节，链接后整镜像与原版一致（段布局、地址、相对跳转）。
3. 每个匹配函数具备：地址标注 + 证据卡 + form 历史 + 独立 verifier 复核记录。
4. 不接受 CHEAT：inline asm、`.word`、裸地址、`goto` 屏障、`volatile` 钉寄存器、placeholder 名。

---

## 7. 旧项目资产利用

| 资产 | 路径 | 用途 |
|---|---|---|
| 函数表 | `IsPurePC/reports/all_functions/_index.tsv` | 3,967 函数 → `config/symbols` |
| 调用图 | `IsPurePC/artifacts/data/analysis/functions.json` | 拓扑排序，叶函数先做 |
| 全量反汇编 | `IsPurePC/artifacts/data/analysis/disasm_text.txt` | 每函数证据卡 |
| 段表 | `IsPurePC/artifacts/data/analysis/sections.json` | ld 脚本 |
| 原版 ELF | `IsPurePC/artifacts/data/samples/SLPM_665.70` | baserom（复制到本项目 `baserom/`，不入库） |
| 行为实现 | `IsPurePC/src/`、`include/` | **仅语义参考**，不编译 |
| PCSX2/探针 | `IsPurePC/tools/`、`tests/` | 可选 L2 二次验证，不进匹配流程 |

---

## 8. 不做什么

- 不追 100%（PS2 无先例；最后 5% 成本指数爆炸）。
- 不用 ProDG / CodeWarrior 工具链。
- 不把行为测试当匹配证据（L0 只认字节）。
- 不在一个会话里跑完项目（多会话 + 状态外置）。
- 不在 spike 通过前写大量 C 或搭自动化。
