extern int FUN_0020f130(int a0);
extern int FUN_0020f170(int a0);

void FUN_00209d08(int a0)
{
    int s0;
    int s1;

    s0 = a0;
    FUN_0020f130(s0);
    s1 = *(int *)(s0 + 0xC);
    if (s1 != 0) {
        *(int *)(s0 + 4) = 1;
        *(int *)(s0 + 0xC) = *(int *)(s1 + 0x3C);
    } else {
        *(int *)(s0 + 4) = 0;
    }
    FUN_0020f170(s0);
}
