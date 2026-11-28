// FUNCTION: SLPM 0x001F70D8  size 104  core 104  (MISS 112/104, 23 words)
// 与 0x001F7070 同形（D_00255EA7 / >>5），同一条延迟槽差：
// ROM 守卫延迟槽是 lui v0,%hi(D_00255EA7)，我们出 daddu a0,sp，整段 +2 词。
extern char D_00255EA7[];
extern int FUN_001f6e78(void);
extern void FUN_00205a50(void *buf);
extern void FUN_00205cb0(void *buf, int a1, int a2);

int FUN_001f70d8(void)
{
    int buf[2];

    if (FUN_001f6e78() != 0)
        return *(unsigned char *)D_00255EA7;
    FUN_00205a50(buf);
    if ((((unsigned int)buf[0] >> 13) & 7) != 0) {
        FUN_00205cb0(buf + 1, 1, 1);
        return (*(unsigned char *)(buf + 1) >> 5) & 1;
    }
    return 0;
}
