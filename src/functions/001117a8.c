// FUNCTION: SLPM 0x001117A8  size 104  core 100
int FUN_001117a8(char *a0, int a1)
{
    int t = *(int *)(a0 + 0x50008);
    int c = *(int *)(a0 + 0x50004);
    int p = *(int *)(a0 + 0x50000);
    int v = t - c;
    int r;

    if (a1 < v)
        v = a1;
    c += v;
    p += v;
    r = p % t;
    *(int *)(a0 + 0x50004) = c;
    *(int *)(a0 + 0x50000) = r;
    return v;
}
