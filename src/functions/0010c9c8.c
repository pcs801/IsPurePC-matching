// FUNCTION: SLPM 0x0010C9C8  size 256  core 252

extern long long D_B25E80[];
extern int D_00270C80;
extern int D_00270C88;

extern int FUN_001dfdc8(int, int);
extern int FUN_001e0ea0(int, int, int, long long);
extern int FUN_001de1a8(int, int, int);

void FUN_0010c9c8(void)
{
    long long v;
    int r;
    int base;

    base = D_00270C80;
    v = D_B25E80[0x1A];
    v = (v & (int)0xFFF9FFFF) | 0x20000;
    FUN_001dfdc8(base, 1);
    r = FUN_001e0ea0(base, 0, 0x47, v);
    FUN_001de1a8(D_00270C88, 0, base);

    D_00270C80 = D_00270C80 + r * 16;
    base = D_00270C80;
    v = D_B25E80[0x2A];
    v = (v & (int)0xFFF9FFFF) | 0x20000;
    FUN_001dfdc8(base, 1);
    r = FUN_001e0ea0(base, 0, 0x48, v);
    FUN_001de1a8(D_00270C88, 0, base);
    D_00270C80 = D_00270C80 + r * 16;
}
