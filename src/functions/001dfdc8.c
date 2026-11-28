// FUNCTION: SLPM 0x001dfdc8  size 80  core 80
extern int D_00249D4C;

int FUN_001dfdc8(long long *a0, int a1)
{
    int t0 = a1 + 1;

    a0[0] = t0 | 0x20000000;
    a0[1] = ((long long)(D_00249D4C | t0) << 32) | 0x9000;
    a0[2] = (a1 | 0x8000) | (0x8000LL << 45);
    a0[3] = 0xE;
    return a1 + 2;
}
