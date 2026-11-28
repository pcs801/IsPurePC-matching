extern int FUN_001b28f0(void);
extern int FUN_001ce9b8(void);
extern int FUN_001b8fe0(void);
extern int FUN_001ce9c0(void);

void FUN_001b8f90(void)
{
    FUN_001b28f0();
}

int FUN_001b8fa8(void)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b8fe0();
    FUN_001ce9c0();
    return r;
}
