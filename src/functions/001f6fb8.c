// FUNCTION: SLPM 0x001F6FB8  size 96  core 76
// if (FUN_001f6e78() != 0) return *(short*)D_0255EA0;
// FUN_00205a50(&x); sel = (x >> 13) & 7; return sel ? (x >> 21) : 0x21C;
extern char D_0255EA0[];
extern int FUN_001f6e78(void);
extern void FUN_00205a50(int *);

int FUN_001f6fb8(void)
{
    int x;
    int sel;

    if (FUN_001f6e78() != 0)
        return *(short *)D_0255EA0;
    FUN_00205a50(&x);
    sel = (x >> 13) & 7;
    return sel ? (x >> 21) : 0x21C;
}
