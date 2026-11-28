// FUNCTION: SLPM 0x001C9860  size 64  core 60
// two-arg variant: FUN_001c7ac0(a0,a1); r = FUN_001c98a8(a0,a1); FUN_001c7ad8(); return r;
extern void FUN_001c7ac0(char *, int);
extern int FUN_001c98a8(char *, int);
extern void FUN_001c7ad8(void);

int FUN_001c9860(char *a0, int a1)
{
    int r;

    FUN_001c7ac0(a0, a1);
    r = FUN_001c98a8(a0, a1);
    FUN_001c7ad8();
    return r;
}
