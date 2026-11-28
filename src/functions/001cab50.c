// FUNCTION: SLPM 0x001CAB50  size 120  core 120
extern int D_00240F34;
extern int D_002411C8;
extern int D_00240F3C;
extern void FUN_001bfe48(int a0);
extern void FUN_0020dd90(int a0);
extern void FUN_001c0130(void);

void FUN_001cab50(void)
{
    if (--D_00240F34 != 0)
        return;
    FUN_001bfe48(D_002411C8);
    D_002411C8 = 0;
    if (D_00240F3C != 0) {
        FUN_0020dd90(D_00240F3C);
        D_00240F3C = 0;
    }
    FUN_001c0130();
}
