extern int FUN_001ce9b8(void);
extern int FUN_001b7ef8(int a0);
extern int FUN_001ce9c0(void);

int FUN_001b7ec0(int a0)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b7ef8(a0);
    FUN_001ce9c0();
    return r;
}
