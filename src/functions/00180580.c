// FUNCTION: SLPM 0x00180580  size 56  core 56
extern int FUN_0017f6e8(void *p);
extern void FUN_00180240(void *q, int n);

int FUN_00180580(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f6e8(p))
        return 0;
    FUN_00180240(q, 128 - q[3]);
    return 0;
}
