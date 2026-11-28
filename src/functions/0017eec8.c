// FUNCTION: SLPM 0x0017EEC8  size 56  core 56
extern int FUN_0017f298(void *p);
extern void FUN_0017e708(void *q, int n);

int FUN_0017eec8(char *p)
{
    int *q = *(int **)(p + 68);

    if (FUN_0017f298(p))
        return 0;
    FUN_0017e708(q, 128 - q[3]);
    return 0;
}
