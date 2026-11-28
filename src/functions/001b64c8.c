extern void FUN_001ce9b8(int *p, int b, int c);
extern int FUN_001b6520(int *p, int b, int c);
extern void FUN_001ce9c0(void);

int FUN_001b64c8(int *p, int b, int c)
{
    int r;

    FUN_001ce9b8(p, b, c);
    r = FUN_001b6520(p, b, c);
    FUN_001ce9c0();
    return r;
}
