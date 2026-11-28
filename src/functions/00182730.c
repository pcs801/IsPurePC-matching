// FUNCTION: SLPM 0x00182730  size 56  core 56
extern int FUN_0017f298(void *p);
extern void FUN_00182428(void *q, int n);

int FUN_00182730(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f298(p))
        return 0;
    FUN_00182428(q, 128 - q[3]);
    return 0;
}
