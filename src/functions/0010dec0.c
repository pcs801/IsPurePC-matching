extern int D_00270C80;
extern int D_00270C88;
extern int D_00270AC8;
extern int FUN_001dfdc8(int, int);
extern int FUN_001e0ea0(int, int, int, int);
extern int FUN_001de1a8(int, int, int);

void FUN_0010dec0(void)
{
    int base;
    int n;

    base = D_00270C80;
    n = FUN_001dfdc8(base, 1);
    FUN_001e0ea0(base, 0, 0x22, (D_00270AC8 == 0) ? 3 : 2);
    FUN_001de1a8(D_00270C88, 0, base);
    D_00270C80 = D_00270C80 + (n << 4);
}