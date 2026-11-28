extern int FUN_0017f298(char *p);
extern void FUN_001811d8(int *q, int v);

int FUN_00181690(char *p)
{
    int *q = *(int **)(p + 0x44);
    int v;

    if (FUN_0017f298(p) != 0)
        return 0;
    v = *(int *)((char *)q + 0xC);
    FUN_001811d8(q, 128 - v);
    return 0;
}
