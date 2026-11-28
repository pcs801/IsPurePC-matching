extern void FUN_001ce9b8(void);
extern int FUN_001b8008(int *p);
extern void FUN_001ce9c0(void);

int FUN_001b7fd0(int *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b8008(p);
    FUN_001ce9c0();
    return r;
}
