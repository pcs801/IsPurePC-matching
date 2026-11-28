extern int D_00270CC4;
extern int FUN_00204f68(int a0, int a1, int a2);

int FUN_00204d40(int a0, int a1, int a2, int a3)
{
    int r;

    D_00270CC4 = 0;
    r = FUN_00204f68(a1, a2, a3);
    *(int *)(a0) = r;
    return r;
}
