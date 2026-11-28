extern void FUN_00117dc0(char *p);

int FUN_00119590(char *p)
{
    int *q = *(int **)(p + 0x44);

    q[2] = q[3] + *(int *)((char *)q[2] + 4);
    FUN_00117dc0(p);
    return 0;
}
