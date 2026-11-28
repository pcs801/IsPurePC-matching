extern int FUN_001fc9d4(int b);
extern void FUN_001d08f0(int a0, int a1, int a2, int a3, int a4);

void FUN_001d11e0(char *p, int b)
{
    int v = FUN_001fc9d4(b);

    FUN_001d08f0(b, v, (int)(p + 0xA22), (int)(p + 0xA24), (int)(p + 0xA26));
    *(short *)(p + 0xA20) = 0;
}
