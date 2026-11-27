# SLPM_665.70 程序地图（m26 · 证据版）

> 数据源：build/m26-program-map-data.json、build/m26-semantic.json、build/m26-semantics/*.md、config/symbols.csv、asm/1000.s。
> 每条结论前缀：**[证据]** = 直接可从上述文件读出；**[推测]** = 由证据外推，未验证。

## 1. 程序身份与规模
- **[证据]** 主执行体 `baserom/SLPM_665.70`（PS2 ELF 主程序，SLPM-66570 编号）。函数表 3966 个符号，函数体合计 1,124,756 B。
- **[证据]** 已匹配 345 / 3966（8.7%）。游戏代码区 0x00100000–0x00204FFF 约 3639 个函数；0x00205000–0x00211830 的 327 个函数是静态链接的 PS2 OS/库区。
- **[证据]** symbols.csv 的 75 个命名符号里 68 个是 SDK 例程：SetGsCrt、_ExecPS2、CreateThread/DeleteThread、CreateSema/SignalSema/WaitSema/PollSema、FlushCache、sceSifSetDma/SetDChain/SetReg、GsGetIMR/GsPutIMR、Deci2Call、GetMemorySize、_InitTLB、RFU116_SetSyscall 等。
- **[推测]** 标题类字符串不在样本中，无法从二进制确认作品名；只能确认它是 2006 年前后、绑定 CRI 中间件的 PS2 游戏主程序。

## 2. 入口与启动序列
- **[证据]** 入口 `entry` = 0x00100008，1104 B。前 30 条把 $at…$ra 全部清零（`padduw $x,$zero,$zero`），随后清 FPU 累加器/$f0-$f31 并 `ctc1 $zero,31`，末尾加载 D_00270A80 与 D_1BA2608 —— 典型 crt0：清寄存器 → 清 FPU → 准备栈/堆边界。
- **[证据]** 紧接着 0x0010012C 是**按字节清 BSS** 的自循环（`sb $zero,0($v0)` + `j` 回跳），0x00100158 是它的 16 字节对齐版本（`sq $zero,0($v0)` + `j` 回跳）。这是第二个硬证据：两段内存清零。
- **[证据]** 之后 0x00100178（59 条）、FUN_00100458（640 B）、FUN_001006d8（616 B）、FUN_00100940（688 B）依次排列且 **callers 全为 0**，说明它们不经 `jal` 调用，而是被 crt0/跳转表间接进入（库初始化段）。
- **[证据]** 启动顺序中的“游戏 main”已定位为 0x0010D788（见 §3）：crt0 在 0x001001C0 设 `gp=D_2779F0`，0x001001C8 / 0x001001E4 用 `syscall`（v1=0x3C/0x3D）取栈/堆上界，`ei` 后 `jal FUN_0010d788`。样本里的 ADXT/CVFS 版本串（Build:Feb 22 2006）与初始化段相邻，支持“库先于游戏逻辑初始化”。

## 3. 主循环（已定位）
- **[证据]** 主线程入口 = **FUN_0010D788（0x0010D788，696 B / 174 条）**：全程序里它的 caller 只有 `entry`（0x00100008）一个——crt0 在 `ei` 开中断之后 `jal FUN_0010d788`，返回路径尾跳 0x001FAD28→0x00100248。把握度：**高**。
- **[证据]** 帧循环体 = **0x0010D850–0x0010DA38**，函数内只有 1 个回跳 `b .L0010D850`（0x0010DA38），构成无限循环。每帧顺序：`FUN_00105fb8` / `FUN_001fbe00` / `FUN_001b1af0` 三个帧首钩子 → 十余个子系统更新（0x001dde30、0x0019ec30、0x0019b688、0x0019b710、0x0019ccc0、0x00102008、0x0019daf8、0x0017ef80）→ 三次 `FUN_00108478(r,g,b)` 设清屏色（0xFF,0xFF,0xFF → 0xFF → 0x40,0x40,0x40）→ `WaitSema(gp[-0x6D64])` 帧同步 → 自旋 → `FlushCache(0)` 并写 0x10000000 → `FUN_001de098` 失败重试 → 帧计数 `gp[-0x6DB0]++`。
- **[证据]** 帧同步协议可由置/等/清三连推出：0x0010D9B0 `gp[-0x6DDC]=1`（向 VSync 中断声明本帧就绪）→ 0x0010D9B8 `WaitSema` 阻塞到 ISR `SignalSema` → 0x0010D9E4 `beq $v0,1` 自旋等该标志被 ISR 清 0；0x0010D9C4 / 0x0010D9F4 两处 `sltiu ...,1` 是布尔取反（toggle）。
- **[证据]** 同骨架的服务线程（非主循环）：**0x0010BC40**（176 B，由 0x0010BB98 用栈上 ThreadParam 调 CreateThread 创建；`WaitSema` → `FUN_0020d520(0x0026FE18,0x5003)` 与 `(0x0026FE20,0x4806)` 两条命令 → `FUN_001f5de0` 轮询 → 回跳），把握度**中**（SIF/GIF 服务线程）；**0x0010EC20**（120 B，由 0x0010E910 创建；`D_825840+0x40=1` 后 `while(lw +0x4C==0)` 自旋 → `SignalSema` → 回跳），把握度**中低**（等硬件就绪）。
- **[证据]** 另两条线程：**0x001F4420**（552 B，callers 为空＝独立线程；`WaitSema` → `ExitDeleteThread` 收尸 → `CreateThread` → `FUN_00206ae0`（全程序唯一调 `_StartThread` 处）→ `ChangeThreadPriority` → 回跳）是**线程回收器**，把握度中；**0x001113B8**（24 B：`RotateThreadReadyQueue(1)` 无限循环）是 **idle 线程**，把握度高但显然不是主循环。
- **[证据]** CreateThread 共 16 处，可读出入口的有：0x0010BB98→0x0010BC40、0x0010E910→0x0010EC20、0x0010EBB0→0x0010E468、0x00110D30→0x001113B8 与 0x001127E0、0x001B0DA8→0x001B0730；即游戏自有线程层集中在 0x0010xxxx/0x0011xxxx/0x001B0xxx。
- **[推测]** crt0 在 0x00100198 设 `gp=D_2779F0`，0x001001C8 / 0x001001E4 用 `syscall`（v1=0x3C/0x3D）取栈与堆上界，`ei` 后直接 `jal FUN_0010d788`——因此 FUN_0010D788 就是 C 的 `main`，它自己不返回（循环无出口，只有异常/退出路径尾跳 0x001FAD28）。
- **已排除**：SetVSyncFlag（唯一 caller 是 SDK 内部 0x00205EC0，游戏侧不直接调）；FlushCache 的 58 个调用点（散在 I/O/DMA，非单一循环体）；0x00100458 / 0x001006d8 / 0x00100940（callers=0 的库初始化段，函数内无回跳）；0x0010012C / 0x00100158（BSS 清零循环，crt0 内部）。
## 4. 子系统划分（按证据强度排序）
- **音频（CRI ADX + MIDI）**：**[证据]** 字符串 `ADXRT Ver.3100 Build:Feb 22 2006`、`MARK:adxt_obj`、`MARK:lsc_obj`、`SJ/PS2EE Ver.6.36`、`PL2ENC Ver.1.02`、`ezMidi INIT err:%d`、`Midi_Init Can't alloc heap sq_hd/bd_trans`、`loop:%d vol:%d, pan l:%d r:%d`、`ADXT_STAT_STOP/PLAYEND`；源码侧有 0x00107990（音量×128÷128×256 缩放）、0x00104E48（关 0–5 通道）、0x001061D8（6 字节通道表项开关）。
- **文件系统/资源（CRI CVFS）**：**[证据]** `CVFS/PS2EE Ver.2.53`、`data.dat`、`icon.sys`/`icon.ico`；0x0017EFA0（按 id 查 12 字节表项初始化全局单例 D_8604D0，表基址 D_002193D0、表项 12 B×≤256）。
- **GS/图形与 DMA**：**[证据]** libgraph/libgp/libdma/libpkt/libvu0 版本串齐全，SetGsCrt/GsGetIMR/GsPutIMR/sceSifSetDChain 已命名；游戏侧 FlushCache 36 个调用点。**[推测]** 0x0019xxxx 段（0x0019F4E0 81 callers、0x0019EEA0 70、0x0019F1C0 68、0x0019DAF8 39）是该驱动的封装层。
- **存档/memcard 与 UI**：**[证据]** `PsIIlibmc 3100`、`Save Game`/`Save System`/`Load Quick`/`Load Game`/`Load System`/`ShortCut`/`ShortCut01`/`ShortCut02`/`Promtion`、`Sys_MsgTblNum mode err` 等 4 条断言串；0x00104648（16 位属性编码解码：2 位 tag + 13 位索引，0x4000 查 short 值表 D_A94700、0x8000 查位图取位）。
- **RPC/SIF 与同步**：**[证据]** sceSifSetDma/isceSifSetDma/sceSifSetReg/sceSifGetReg/sceSifStopDma 全命名，plus CreateSema/SignalSema/WaitSema/FlushCache 的高调用密度；**[证据]** 两对空钩子 0x001CE9B8/0x001CE9C0（105 callers）与 0x001C46A0/0x001C46A8（19 callers）是整段函数统一插入的 enter/exit 桩。
- **视频（MPEG/IPU）**：**[证据]** `PsIIlibmpeg 3100`、`PsIIlibipu 3100`、`PsIIlibsdr 3100` 版本串；**[推测]** 用于 CG 播放，具体入口未定位。
- **网络/其他库**：**[证据]** `PsIIlibnet 3100`、`PsIInetcnfif3100`、`libmrpc`、`libscf`、`libkernl`；**[推测]** 只做底层链接，游戏逻辑未必使用网络。

## 5. 已破解函数按子系统归类（29 篇 m26-semantics 笔记）
- **音频**：0x00107990（音量缩放→0xD1 通道）、0x00104E48（停通道 0,4,5,1,2,3）、0x00104E20（清 492 B 缓冲 + 触发）、0x001061D8（MIDI/通道开关，受 D_A98DA7 门控）。
- **图形/坐标与插值**：0x001A8208 / 0x001A8228（Q12 插值槽 set/set-target）、0x001E3D90 / 0x001E3DA0（整数三元组 set/commit）、0x00123868 / 0x00123940 / 0x001241D0（当前槽 D_00270CB0[*base] 字段读写，元素 24568 B）。
- **资源/表**：0x0017EFA0（单例初始化 + 12 B 表）、0x00105818（全局指针表 u16@+8）、0x00105760（位图 set/clear 后刷新）、0x00104648（16 位属性编码解码）。
- **UI/菜单**：0x001061D8 与 0x00104648 兼属本块（通道开关与菜单表）；UI 其余部分尚未破解。
- **包装/粘合**：0x001CAE08 / 0x001CAE38（→FUN_001cad18 传 1/2）、0x001CAE20 / 0x001CAEB0（→FUN_001cad78 传 1/2）、0x001B3E40（+4 解引用转发）、0x001B3D80（p[15] set/get，符号 16 B 含两个函数）。
- **全局 setter**：0x00123568（D_00270CB0）、0x0010C110（D_00270AC0）、0x001CFF08（p[3] getter）、0x00155B68（二元组重置）。
- **插桩层**：0x001CE9B8/0x001CE9C0、0x001C46A0/0x001C46A8（空钩子对，覆盖 0x001AF7D0–0x001BB628 与 0x001C3910–0x001C4630 两段）。

## 6. 未破解的优先目标（按调用中心度）
1. **0x001FBB84（160 callers）**——**[推测]** memset：依据 0x00104E20 的调用形态 `FUN_001fbb84(D_1B73FC0, 0, 0x1EC)`（dst, 0, len）。破解它可一次性解释 160 个调用点。
2. **0x00117DC0（124 callers）**——**[证据] 不是 memcpy**：单参数查表初始化（读 p[0x44]→+8→lbu 得 idx，取 D_00213590+idx*24 的 w0/w1，写 p[0]/p[0xD]/p[0x10]，尾跳 FUN_001fc8c0(p+0x14,w1)）；124 个 caller 只设 a0 并丢弃返回值。
3. **0x0020F180 / 0x0020F130（各 112 callers）**——**[证据]** 位于 0x0020Fxxx 区（SDK 侧，RFU116_SetSyscall 也在附近），**[推测]** syscall 包装或浮点/数学库入口。
4. **0x001CF618（88）、0x0019F4E0（81）、0x00209838（76）、0x001FC8C0（76）、0x001DE1A8（75）、0x001A09A0（71）、0x0019EEA0（70）、0x0019F1C0（68）**——0x0019xxxx/0x001Cxxxx/0x001Fxxxx 三段的中心函数，**[推测]** 分别是 GS 驱动、渲染/资源管理、libc 层。
5. **0x001AF7D0 / 0x001AF7E8（各 48）**——**[证据]** 与 0x001CE9B8/0x001CE9C0 相邻且同在插桩段内，**[推测]** 是这对钩子的真正实现（未被 match 的 8 B/16 B 变体）。

## 7. 结论
- **[证据]** 程序结构 = crt0 + 静态链接的 PS2 SDK（graph/dma/pkt/pad/mc/cdvd/mpeg/ipu/net/kernl）+ CRI 中间件（ADX/CVFS/SJ/PL2）+ 游戏逻辑；音频与存档菜单字符串是该中间件栈的直接指纹。
- **[证据]** 函数级匹配率 8.7%（345/3966），且集中在 0x001B/0x001C/0x001A/0x0010 段——即"小、纯、无外部依赖"的函数先被吃掉，与工具链的 easy/medium 分级一致。
- **[推测]** 下一步性价比最高的是 libc 替换层（0x001FBB84/0x00117DC0）与槽/插值一族，因为它们的调用面最宽，且已有语义笔记可复用。

- **[证据]** 主循环已定位（§3）：主线程 0x0010D788 + 帧循环 0x0010D850–0x0010DA38；程序不是单线程裸循环，而是“主线程逐帧循环 + 至少 6 个 CreateThread 服务线程（SIF/GIF 0x0010BC40、硬件就绪 0x0010EC20、线程回收 0x001F4420、idle 0x001113B8 等）”的多线程结构。