extern void FUN_001ce9b8(void);
extern int FUN_001b90e0(int *p);
extern void FUN_001ce9c0(void);

int FUN_001b90a8(int *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b90e0(p);
    FUN_001ce9c0();
    return r;
}
