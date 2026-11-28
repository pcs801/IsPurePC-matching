// FUNCTION: SLPM 0x001AC148  size 56  core 56
extern char D_002241B4[];
extern int FUN_001ac0c0(void);
extern void FUN_001ac5d0(int a0);

int FUN_001ac148(void)
{
    int r = FUN_001ac0c0();

    FUN_001ac5d0(0);
    *(int *)D_002241B4 = 0;
    return r;
}
