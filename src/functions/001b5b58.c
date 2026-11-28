// FUNCTION: SLPM 0x001B5B58
extern void FUN_001ce9b8(void);
extern int FUN_001b5b90(void);
extern void FUN_001ce9c0(void);

int FUN_001b5b58(void)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b5b90();
    FUN_001ce9c0();
    return r;
}
