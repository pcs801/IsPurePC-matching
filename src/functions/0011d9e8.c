// FUNCTION: SLPM 0x0011D9E8  size 48 (core 44)
extern void FUN_00117dc0(char *p);

int FUN_0011d9e8(char *p)
{
    int *q = *(int **)(p + 0x44);

    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
