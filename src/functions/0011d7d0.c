extern void FUN_00117760(char *p);
extern void FUN_00117dc0(char *p);

int FUN_0011d7d0(char *p)
{
    int *q = *(int **)(p + 0x44);

    q[2] = q[2] + 4;
    FUN_00117760(p);
    FUN_00117dc0(p);
    return 0;
}
