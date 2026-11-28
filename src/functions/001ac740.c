// FUNCTION: SLPM 0x001AC740  size 72  core 72
extern char D_002650B0[];
extern char D_002650E8[];
extern void FUN_001cf618(void *a0);

int FUN_001ac740(unsigned int a0, int a1)
{
    if (a0 >= 0x100) {
        FUN_001cf618(D_002650B0);
        return -3;
    }
    if (a1 != 0)
        return 0;
    FUN_001cf618(D_002650E8);
    return -3;
}
