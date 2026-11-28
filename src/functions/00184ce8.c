extern int FUN_0017f298(int a0);
extern int FUN_001843b0(int a0, int a1, int a2, int a3);

int FUN_00184ce8(int a0)
{
    int s0;
    int r;

    s0 = *(int *)(a0 + 0x44);
    r = FUN_0017f298(a0);
    if (r != 0)
        return 0;
    FUN_001843b0(s0, *(int *)(s0 + 0xC), 0, 0);
    return 0;
}
