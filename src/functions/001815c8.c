extern int FUN_0017f6e8(char *p);
extern void FUN_00180e10(int *q, int v);

int FUN_001815c8(char *p)
{
    int *q = *(int **)(p + 0x44);
    int v;

    if (FUN_0017f6e8(p) != 0)
        return 0;
    v = q[3];
    FUN_00180e10(q, v);
    return 0;
}
