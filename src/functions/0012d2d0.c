// FUNCTION: SLPM 0x0012D2D0  size 56  core 56
extern char *D_00270CAC;
extern void FUN_00107910(int v);
extern void FUN_001173e8(int a0, int a1);

void FUN_0012d2d0(int v)
{
    *(unsigned char *)(D_00270CAC + 0x40000 - 3328) = v;
    FUN_00107910(v);
    FUN_001173e8(*(unsigned char *)(D_00270CAC + 0x40000 - 3328), 1);
}
