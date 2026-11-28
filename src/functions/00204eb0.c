extern int D_00270CC4;
extern int FUN_00205158(int a0, int a1);

int FUN_00204eb0(int a0, int a1, int a2)
{
    int r;

    D_00270CC4 = 0;
    r = FUN_00205158(a1, a2);
    *(int *)(a0) = r;
    return r;
}
