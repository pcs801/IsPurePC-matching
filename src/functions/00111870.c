// FUNCTION: SLPM 0x00111870  size 48 (core 44)
// take = min(n, *(int*)(p+0x50004)); *(int*)(p+0x50004) -= take; return take;
// Status: 44/44 bytes, 8 words off - target keeps the 0x50000 base in v0, we get v1.
int FUN_00111870(char *p, int n)
{
    int cur = *(int *)(p + 0x50004);
    int take = (n < cur) ? n : cur;

    *(int *)(p + 0x50004) = cur - take;
    return take;
}
