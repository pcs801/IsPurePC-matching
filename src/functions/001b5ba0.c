// FUNCTION: SLPM 0x001B5BA0
extern void FUN_001ce9b8(void);
extern int FUN_001b5bd8(int);
extern void FUN_001ce9c0(void);

int FUN_001b5ba0(int a0)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b5bd8(a0);
    FUN_001ce9c0();
    return r;
}
