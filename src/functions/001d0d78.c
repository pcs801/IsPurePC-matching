extern void FUN_001d0cb0(char *p, int v);

int FUN_001d0d78(char *p, int v)
{
    FUN_001d0cb0(p, v);
    *(int *)(p + 0x1AC) = v;
    return 0;
}
