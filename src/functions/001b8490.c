extern int FUN_001ce9b8(int a0, int a1);
extern int FUN_001b84d8(int a0, int a1);
extern int FUN_001ce9c0(void);

int FUN_001b8490(int a0, int a1)
{
    int r;

    FUN_001ce9b8(a0, a1);
    r = FUN_001b84d8(a0, a1);
    FUN_001ce9c0();
    return r;
}
