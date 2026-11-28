extern void FUN_001cff40(int a0, int a1, int a2, int a3, int t0);
extern void FUN_001cffa0(int a0);

void FUN_001cd5d0(char *p, int n)
{
    char *q = p + 72;
    int a3 = *(int *)(q + 20) + *(int *)(q + 32) * 2;

    FUN_001cff40(*(int *)(p + 8), *(int *)q, n * 2, a3, a3 + *(int *)(q + 28) * 2);
    FUN_001cffa0(*(int *)(p + 8));
}
