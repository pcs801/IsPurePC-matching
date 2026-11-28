// FUNCTION: SLPM 0x001CA000  size 56
extern void FUN_001c7ac0(int);
extern int FUN_001ca038(int);
extern void FUN_001c7ad8(void);

int FUN_001ca000(int a0)
{
    int r;

    FUN_001c7ac0(a0);
    r = FUN_001ca038(a0);
    FUN_001c7ad8();
    return r;
}
