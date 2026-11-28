// FUNCTION: SLPM 0x001F7070  size 104  core 104  (MISS 112/104, 23 words)
// ROM: beqz v0,+3 ; delay lui v0,%hi(D_00255EA6) ; b epilogue ; lbu v0
// got: beqz v0,+5 ; delay daddu a0,sp  (GCC 把首个调用的 &buf 提到守卫延迟槽,
//  ROM 放的是返回路径的 lui) -> 返回块 4 词 + 对齐 nop, 整段 +2 词.
// 已试: int buf[2] / char buf[8] / 两个标量 / r=0 单出口 / if-else 反写 / -fno-delayed-branch.
extern char D_00255EA6[];
extern int FUN_001f6e78(void);
extern void FUN_00205a50(void *buf);
extern void FUN_00205cb0(void *buf, int a1, int a2);

int FUN_001f7070(void)
{
    int buf[2];

    if (FUN_001f6e78() != 0)
        return *(unsigned char *)D_00255EA6;
    FUN_00205a50(buf);
    if ((((unsigned int)buf[0] >> 13) & 7) != 0) {
        FUN_00205cb0(buf + 1, 1, 1);
        return (*(unsigned char *)(buf + 1) >> 4) & 1;
    }
    return 0;
}
