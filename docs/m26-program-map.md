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
- **[推测]** 启动顺序：crt0（清寄存器/FPU/BSS）→ 库初始化 → `_InitTLB`/`GetMemorySize` 类调用 → 游戏 main。样本字符串里的 ADXT/CVFS 版本串（Build:Feb 22 2006）与这些初始化段相邻，支持"库先于游戏逻辑初始化"。

## 3. 主循环
- **[证据]** 游戏侧没有直接调用 SetVSyncFlag（其唯一 caller 是 SDK 内部 0x00205EC0）；FlushCache 有 36 个 caller（0x00100008 入口、0x0010BE28、0x0019xxxx、0x001E8xxx 等），散布在 I/O 与 DMA 代码里，不是单一的循环体。
- **[推测]** 主循环是"VSync/线程轮询 + 每帧刷新"结构：依据是 libgraph/libdma/libpkt + libpad 全链接、信号量使用密集（CreateSema 39 callers / SignalSema 61 / WaitSema 59），这种组合几乎只出现在逐帧驱动（读 pad → 提交 DMA 链 → 等 VSync）的游戏里。循环体本身的地址尚未定位，是本项工作最大的空白。

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
2. **0x00117DC0（124 callers）**——**[推测]** memcpy/memmove，与上面成对出现；同属 libc 替换层。
3. **0x0020F180 / 0x0020F130（各 112 callers）**——**[证据]** 位于 0x0020Fxxx 区（SDK 侧，RFU116_SetSyscall 也在附近），**[推测]** syscall 包装或浮点/数学库入口。
4. **0x001CF618（88）、0x0019F4E0（81）、0x00209838（76）、0x001FC8C0（76）、0x001DE1A8（75）、0x001A09A0（71）、0x0019EEA0（70）、0x0019F1C0（68）**——0x0019xxxx/0x001Cxxxx/0x001Fxxxx 三段的中心函数，**[推测]** 分别是 GS 驱动、渲染/资源管理、libc 层。
5. **0x001AF7D0 / 0x001AF7E8（各 48）**——**[证据]** 与 0x001CE9B8/0x001CE9C0 相邻且同在插桩段内，**[推测]** 是这对钩子的真正实现（未被 match 的 8 B/16 B 变体）。

## 7. 结论
- **[证据]** 程序结构 = crt0 + 静态链接的 PS2 SDK（graph/dma/pkt/pad/mc/cdvd/mpeg/ipu/net/kernl）+ CRI 中间件（ADX/CVFS/SJ/PL2）+ 游戏逻辑；音频与存档菜单字符串是该中间件栈的直接指纹。
- **[证据]** 函数级匹配率 8.7%（345/3966），且集中在 0x001B/0x001C/0x001A/0x0010 段——即"小、纯、无外部依赖"的函数先被吃掉，与工具链的 easy/medium 分级一致。
- **[推测]** 下一步性价比最高的是 libc 替换层（0x001FBB84/0x00117DC0）与槽/插值一族，因为它们的调用面最宽，且已有语义笔记可复用。
