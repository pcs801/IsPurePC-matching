// FUNCTION: SLPM 0x001C8798  size 64  core 60
extern void FUN_001c7ac0(char *, int);
extern int FUN_001c87e0(char *, int);
extern void FUN_001c7ad8(void);

int FUN_001c8798(char *a0, int a1)
{
    int r;

    FUN_001c7ac0(a0, a1);
    r = FUN_001c87e0(a0, a1);
    FUN_001c7ad8();
    return r;
}
