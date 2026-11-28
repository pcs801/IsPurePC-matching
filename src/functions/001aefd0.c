// FUNCTION: SLPM 0x001AEFD0
extern void FUN_001af7d0(int);
extern int FUN_001af008(int);
extern void FUN_001af7e8(void);

int FUN_001aefd0(int a0)
{
    int r;

    FUN_001af7d0(a0);
    r = FUN_001af008(a0);
    FUN_001af7e8();
    return r;
}
