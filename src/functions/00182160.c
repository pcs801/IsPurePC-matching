// FUNCTION: SLPM 0x00182160  size 56  core 56
extern int FUN_0017f6e8(void *p);
extern void FUN_00181e80(void *q, int n);

int FUN_00182160(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f6e8(p))
        return 0;
    FUN_00181e80(q, 128 - q[3]);
    return 0;
}
