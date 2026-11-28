// FUNCTION: SLPM 0x001ACDE0  size 160  core 149
extern void FUN_001af7d0(char *, int, int, int, int, int);
extern int FUN_001ace68(char *, int, int, int, int, int);
extern void FUN_001af7e8(void);

int FUN_001acde0(char *a0, int a1, int a2, int a3, int t0, int t1)
{
    int r;

    FUN_001af7d0(a0, a1, a2, a3, t0, t1);
    r = FUN_001ace68(a0, a1, a2, a3, t0, t1);
    FUN_001af7e8();
    return r;
}
