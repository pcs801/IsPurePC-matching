extern int FUN_001dde30(int a0);

int FUN_001dddf0(int a0, int a1, int a2)
{
    int s0;

    s0 = a2;
    if (a1 != 0 && a0 != 0) {
        *(int *)(a0) = a1;
        *(int *)(a0 + 0xC) = s0;
        FUN_001dde30(a0);
    }
    return s0 + 1;
}
