extern int FUN_001ce9b8(void);
extern int FUN_001b7d78(int a0);
extern int FUN_001ce9c0(void);

int FUN_001b7d40(int a0)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b7d78(a0);
    FUN_001ce9c0();
    return r;
}
