extern void FUN_001ce9b8(int *p, int b, int c);
extern int FUN_001b9740(int *p, int b, int c);
extern void FUN_001ce9c0(void);

int FUN_001b96e8(int *p, int b, int c)
{
    int r;

    FUN_001ce9b8(p, b, c);
    r = FUN_001b9740(p, b, c);
    FUN_001ce9c0();
    return r;
}
