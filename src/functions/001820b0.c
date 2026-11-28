// FUNCTION: SLPM 0x001820B0  size 56  core 56
extern int FUN_0017f6e8(void *p);
extern void FUN_00181c88(void *q, int n);

int FUN_001820b0(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f6e8(p))
        return 0;
    FUN_00181c88(q, 128 - q[3]);
    return 0;
}
