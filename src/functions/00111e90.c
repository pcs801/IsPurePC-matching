// FUNCTION: SLPM 0x00111E90  size 128  core 128
extern int FUN_00112260(int);
extern int FUN_001e9090(int, int, int, int, int, int, ...);

int FUN_00111e90(char *p)
{
    int v;

    *(int *)p = 3;
    FUN_00112260(0);
    v = FUN_001e9090(1, 0x80E0, 1, 2, 0, 0);
    *(int *)(p + 0x50) = (v & 0xFFFFFF) - *(int *)(p + 0x44);
    return FUN_001e9090(1, 0x80D0, 1, 0, *(int *)(p + 0x58), 0x4000, 0x800);
}
