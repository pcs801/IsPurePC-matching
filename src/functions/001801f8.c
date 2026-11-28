// FUNCTION: SLPM 0x001801F8  size 56  core 56
extern int FUN_0017f6e8(void *p);
extern void FUN_00180058(void *q, int n);

int FUN_001801f8(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f6e8(p))
        return 0;
    FUN_00180058(q, 128 - q[3]);
    return 0;
}
