extern int FUN_0017f298(char *p);
extern void FUN_00180240(int *q, int v);

int FUN_00180540(char *p)
{
    int *q = *(int **)(p + 0x44);
    int v;

    if (FUN_0017f298(p) != 0)
        return 0;
    v = q[3];
    FUN_00180240(q, v);
    return 0;
}
