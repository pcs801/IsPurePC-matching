// FUNCTION: SLPM 0x001AEDB8
extern void FUN_001af7d0(int);
extern int FUN_001aedf0(int);
extern void FUN_001af7e8(void);

int FUN_001aedb8(int a0)
{
    int r;

    FUN_001af7d0(a0);
    r = FUN_001aedf0(a0);
    FUN_001af7e8();
    return r;
}
