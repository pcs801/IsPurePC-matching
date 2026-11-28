extern int FUN_00171cc8(int a0, int a1, int a2, int a3);

int FUN_00173a78(int p, int a1, int a2, int a3, int t0)
{
    int s;
    int h;

    s = *(unsigned short *)(p + 6) + a1;
    h = *(signed char *)(p + 4);
    return FUN_00171cc8((h << 16) | (s & 0xFFFF), a2, a3, t0 & 0xFFFF);
}
