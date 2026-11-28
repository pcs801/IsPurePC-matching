// FUNCTION: SLPM 0x001AF1C0  size 144  core 140
extern void FUN_001af7d0(void);
extern void FUN_001af7e8(void);
extern int FUN_001af250(int a0, int a1, int a2, int a3, int a4, int a5, int *buf);

int FUN_001af1c0(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int buf[4];
    int r;

    FUN_001af7d0();
    r = FUN_001af250(a0, a1, a2, a3, a4, a5, buf);
    FUN_001af7e8();
    return r;
}
