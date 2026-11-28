extern int FUN_0017f6e8(char *p);
extern void FUN_0017e708(int *q, int v);

int FUN_0017ef10(char *p)
{
    int *q = *(int **)(p + 0x44);
    int v = *(int *)((char *)q + 0xC);

    if (FUN_0017f6e8(p) != 0)
        return 0;
    FUN_0017e708(q, v);
    return 0;
}
