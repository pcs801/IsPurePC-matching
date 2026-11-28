// FUNCTION: SLPM 0x001D56C0  size 128  core 128
extern void FUN_001d5110(char *p, int n);
extern void FUN_001d55c8(char *p, int v);

int FUN_001d56c0(char *p, int n, int *out, int val)
{
    if (out != 0)
        *out = 0;
    if (n < 0x24)
        return -1;
    p[0] = -0x80;
    p[1] = 0;
    FUN_001d5110(p + 2, 0x20);
    FUN_001d55c8(p + 4, val);
    *out = 0x24;
    return 0;
}
