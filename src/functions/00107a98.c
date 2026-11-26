// FUNCTION: SLPM 0x00107A98  size 72  core 72

extern int FUN_0019d950(int, int *, int, int);
extern void FUN_00106a20(void);

void FUN_00107a98(int *p, int v, int n)
{
    p[0] = 1;
    p[1] = 0;
    p[5] = v;
    p[2] = FUN_0019d950((int)FUN_00106a20, p, n, 2);
}
