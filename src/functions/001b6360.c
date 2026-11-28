extern void FUN_001b2950(void);
extern void FUN_001ce9b8(void);
extern int FUN_001b63b0(void);
extern void FUN_001ce9c0(void);

void FUN_001b6360(void)
{
    FUN_001b2950();
}

int FUN_001b6378(void)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b63b0();
    FUN_001ce9c0();
    return r;
}
