extern int D_00270CC4;
extern int FUN_00205178(int a0, int a1);

int FUN_001fc1a8(int a0, int a1, int a2)
{
    int r;

    D_00270CC4 = 0;
    r = FUN_00205178(a1, a2);
    *(int *)(a0) = r;
    return r;
}
