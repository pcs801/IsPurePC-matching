// FUNCTION: SLPM 0x001F6F38  size 64  core 64
extern char D_00255EA2[];
extern int FUN_001f6e78(void);
extern void FUN_00205a50(void *buf);

int FUN_001f6f38(void)
{
    int buf[2];

    if (FUN_001f6e78() != 0)
        return *(unsigned char *)D_00255EA2;
    FUN_00205a50(buf);
    return ((unsigned int)buf[0] >> 1) & 3;
}
