// FUNCTION: SLPM 0x0010C1F0  size 40  core 40 (region = wrapper + stub at 0x10C208)
extern void FUN_0015a2f8(void);
extern int D_00270C54;

void FUN_0010c1f0(void)
{
    FUN_0015a2f8();
}

int FUN_0010c208(void)
{
    D_00270C54 = 3;
    return 1;
}
