// FUNCTION: SLPM 0x00107A50  size 72  core 72

extern int FUN_0019d950(int, int *, int, int);
extern void FUN_00106a20(void);

void FUN_00107a50(int a0, int *p, int n)
{
    p[0] = 0;
    p[1] = a0;
    p[5] = (int)(p + 32);
    p[2] = FUN_0019d950((int)FUN_00106a20, p, n - 0x100, 2);
}
