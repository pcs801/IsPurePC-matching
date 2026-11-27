// FUNCTION: SLPM 0x0010C9C8  size 256  core 252
// best compliant candidate: 252/252 bytes, 2 words differ (bump temp uses v1 where target uses v0)

extern long long D_B25E80[];
extern int D_00270C80;
extern int D_00270C88;

extern int FUN_001dfdc8(int, int);
extern int FUN_001e0ea0(int, int, int, long long);
extern int FUN_001de1a8(int, int, int);

void FUN_0010c9c8(void)
{
    long long v1, v2;
    int n;
    int base;

    base = D_00270C80;
    v1 = D_B25E80[0x1A];
    v1 &= (int)0xFFF9FFFF;
    v1 |= 0x20000;
    n = FUN_001dfdc8(base, 1);
    FUN_001e0ea0(base, 0, 0x47, v1);
    FUN_001de1a8(D_00270C88, 0, base);
    D_00270C80 += n * 16;
    base = D_00270C80;
    v2 = D_B25E80[0x2A];
    v2 &= (int)0xFFF9FFFF;
    v2 |= 0x20000;
    n = FUN_001dfdc8(base, 1);
    FUN_001e0ea0(base, 0, 0x48, v2);
    FUN_001de1a8(D_00270C88, 0, base);
    D_00270C80 += n * 16;
}
