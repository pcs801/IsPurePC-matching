extern int FUN_001c7ac0(int a0, int a1);
extern int FUN_001c7ca0(int a0, int a1);
extern int FUN_001c7ad8(void);

int FUN_001c7c58(int a0, int a1)
{
    int r;

    FUN_001c7ac0(a0, a1);
    r = FUN_001c7ca0(a0, a1);
    FUN_001c7ad8();
    return r;
}
