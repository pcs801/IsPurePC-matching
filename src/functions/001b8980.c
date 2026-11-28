extern int FUN_001b8838(void);
extern int FUN_001ce9b8(int a0);
extern int FUN_001b89d0(int a0);
extern int FUN_001ce9c0(void);

void FUN_001b8980(void)
{
    FUN_001b8838();
}

int FUN_001b8998(int a0)
{
    int r;

    FUN_001ce9b8(a0);
    r = FUN_001b89d0(a0);
    FUN_001ce9c0();
    return r;
}
