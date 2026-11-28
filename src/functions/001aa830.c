// FUNCTION: SLPM 0x001AA830  size 72  core 72
extern int FUN_001a9ed0(int a0, int a1, int *a2, int a3, int a4);

int FUN_001aa830(int a0, int *a1, int a2, int a3)
{
    int r;

    a1[0] = a2;
    a1[1] = a3;
    r = FUN_001a9ed0(a0, 15, a1, 8, 4);
    if (r >= 0)
        return a1[0];
    return -0x21E;
}
