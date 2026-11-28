extern void FUN_001af828(void);
extern void FUN_001ce9b8(void);
extern int FUN_001af9b0(void);
extern void FUN_001ce9c0(void);

void FUN_001af960(void)
{
    FUN_001af828();
}

int FUN_001af978(void)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001af9b0();
    FUN_001ce9c0();
    return r;
}

int FUN_001af9b0(void)
{
    return *(int *)0x00226318 != 0;
}

int FUN_001af9c8(void)
{
    return 0x002658B0;
}

void FUN_001af9d8(int a0)
{
    *(int *)0x0022634C = a0;
}
