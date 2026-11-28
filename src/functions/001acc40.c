// FUNCTION: SLPM 0x001ACC40  size 160  core 149
// 6-arg skeleton: r = MID(a0,a1,a2,a3,t0,t1) with the pre/post calls
extern void FUN_001af7d0(char *, int, int, int, int, int);
extern int FUN_001accc8(char *, int, int, int, int, int);
extern void FUN_001af7e8(void);

int FUN_001acc40(char *a0, int a1, int a2, int a3, int t0, int t1)
{
    int r;

    FUN_001af7d0(a0, a1, a2, a3, t0, t1);
    r = FUN_001accc8(a0, a1, a2, a3, t0, t1);
    FUN_001af7e8();
    return r;
}
