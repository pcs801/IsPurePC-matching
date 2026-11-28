// FUNCTION: SLPM 0x001c3578  size 80  core 76
extern int D_002324E0;
extern int FUN_001c3488(int a0, int a1, int a2, int a3);

int FUN_001c3578(int a0, int *a1)
{
    int *d = &D_002324E0;

    a1[0] = 0;
    a1[1] = 0;
    if (d[0] != 0)
        return FUN_001c3488((int)a1, a0, d[0], d[1]);
}
