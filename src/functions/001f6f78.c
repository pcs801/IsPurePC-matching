// FUNCTION: SLPM 0x001F6F78  size 64  core 60
extern char D_00255EA5[];
extern int FUN_001f6e78(void);
extern void FUN_00205a50(void *buf);

int FUN_001f6f78(void)
{
    int buf[2];

    if (FUN_001f6e78() != 0)
        return *(unsigned char *)D_00255EA5;
    FUN_00205a50(buf);
    return buf[0] & 1;
}
