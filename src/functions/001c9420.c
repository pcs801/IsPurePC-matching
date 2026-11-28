// FUNCTION: SLPM 0x001C9420  size 96  core 88
// int r; FUN_001c7ac0(a0,a1,a2); r = FUN_001c9478(a0,a1,a2); FUN_001c7ad8(); return r;
extern void FUN_001c7ac0(char *, int, int);
extern int FUN_001c9478(char *, int, int);
extern void FUN_001c7ad8(void);

int FUN_001c9420(char *a0, int a1, int a2)
{
    int r;

    FUN_001c7ac0(a0, a1, a2);
    r = FUN_001c9478(a0, a1, a2);
    FUN_001c7ad8();
    return r;
}
