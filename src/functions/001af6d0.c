// FUNCTION: SLPM 0x001AF6D0  size 112  core 112
extern char D_00265888[];
extern int FUN_001cf618(char *msg);
extern int FUN_001b56e8(int a0);
extern void FUN_001af7d0(int a0);
extern int FUN_001af740(int a0);
extern void FUN_001af7e8(void);

int FUN_001af6d0(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00265888);
        return 0;
    }
    return FUN_001b56e8(a0);
}

int FUN_001af708(int a0)
{
    int r;

    FUN_001af7d0(a0);
    r = FUN_001af740(a0);
    FUN_001af7e8();
    return r;
}
