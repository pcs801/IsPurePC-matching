// FUNCTION: SLPM 0x001C9618  size 56
extern void FUN_001c7ac0(int);
extern int FUN_001c9650(int);
extern void FUN_001c7ad8(void);

int FUN_001c9618(int a0)
{
    int r;

    FUN_001c7ac0(a0);
    r = FUN_001c9650(a0);
    FUN_001c7ad8();
    return r;
}
