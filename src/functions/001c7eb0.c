extern void FUN_001c7ac0(int *p, int b, int c);
extern void FUN_001c7f00(int *p, int b, int c);
extern void FUN_001c7ad8(void);

void FUN_001c7eb0(int *p, int b, int c)
{
    FUN_001c7ac0(p, b, c);
    FUN_001c7f00(p, b, c);
    FUN_001c7ad8();
}
