// FUNCTION: SLPM 0x0020A1D0  size 112  core 108  (MISS 124/108, 26 words)
// ROM 帧 -0x30：s0@0x0 / s1@0x10 / ra@0x20（0x8、0x18 各一个未访问 8 字节槽）→
// 原码似有两个 8 字节局部量；我们只压到 -0x20 且多用一个 s2。
// ROM 分支是 sltiu v1,s0,0x20 + bnez（跳到算 p 的块），已按 idx<0x20 写仍反了布局。
// s1 只存 %hi(D_002566E0)、lo 折进两次 lw —— 用 int 标量已复现该形态。
extern int D_002566E0;
extern char D_86FF00[];
extern void FUN_00209f68(void);
extern int FUN_002059e0(int sema);
extern int FUN_002059c0(int sema);

char *FUN_0020a1d0(unsigned int idx)
{
    char *p;

    FUN_00209f68();
    FUN_002059e0(D_002566E0);
    if (idx < 0x20) {
        p = D_86FF00 + idx * 16;
        FUN_002059c0(D_002566E0);
        return p;
    }
    FUN_002059c0(D_002566E0);
    return 0;
}
