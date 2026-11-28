extern int FUN_00118020(int a0);
extern void FUN_00117dc0(void *p);

int FUN_00118238(char *p)
{
    int *q = *(int **)(p + 68);
    int n = FUN_00118020(*(unsigned char *)*(int *)((char *)q + 8));
    int *q2 = *(int **)(p + 68);

    q2[2] = q2[2] + n;
    FUN_00117dc0(p);
    return 0;
}
