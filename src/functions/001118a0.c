// FUNCTION: SLPM 0x001118A0  size 288  core 284
extern char D_002591F0[];
extern char D_002591D0[];
extern char D_8299C0[];
extern int FUN_001fbd78();
extern void FUN_00112260(int);
extern int FUN_0020dc98(int, int, int);
extern void FUN_001fbb84(void *, int, int);
extern void FUN_00112188(int, void *, int);
extern void FUN_001121f8(int);

int FUN_001118a0(char *p, int a1, int a2, int a3)
{
    int b1;
    int b2;

    FUN_00112260(0);
    *(int *)(p + 0x30) = a1;
    *(int *)(p + 0x3C) = a2;
    *(int *)(p + 0x00) = 0;
    *(int *)(p + 0x2C) = 0;
    *(int *)(p + 0x34) = 0;
    *(int *)(p + 0x38) = 0;
    *(int *)(p + 0x40) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x48) = a3;
    *(int *)(p + 0x4C) = 0;
    *(int *)(p + 0x50) = 0;
    b1 = FUN_0020dc98(0, a3, 0);
    *(int *)(p + 0x44) = b1;
    if (b1 == 0) {
        FUN_001fbd78(D_002591D0);
        return 0;
    }
    FUN_001fbd78(D_002591F0, b1, a3);
    b2 = FUN_0020dc98(0, 0x800, 0);
    *(int *)(p + 0x58) = b2;
    if (b2 == 0) {
        FUN_001fbd78(D_002591D0);
        return 0;
    }
    FUN_001fbd78(D_002591F0, b2, 0x800);
    FUN_001fbb84(D_8299C0, 0, 0x800);
    FUN_00112188(*(int *)(p + 0x58), D_8299C0, 0x800);
    FUN_001121f8(0x3FFF);
    return 1;
}
