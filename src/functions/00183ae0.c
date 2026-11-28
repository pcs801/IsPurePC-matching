extern int FUN_0017f298(int a0);
extern int FUN_00183300(int a0, int a1);

int FUN_00183ae0(int a0)
{
    int s0;
    int r;

    s0 = *(int *)(a0 + 0x44);
    r = FUN_0017f298(a0);
    if (r != 0)
        return 0;
    FUN_00183300(s0, *(int *)(s0 + 0xC));
    return 0;
}
