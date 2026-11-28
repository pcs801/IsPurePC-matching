// FUNCTION: SLPM 0x001B7090
extern void FUN_001ce9b8(void);
extern int FUN_001b70c8(int);
extern void FUN_001ce9c0(void);

int FUN_001b7090(int a0)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b70c8(a0);
    FUN_001ce9c0();
    return r;
}
