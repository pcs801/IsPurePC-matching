// FUNCTION: SLPM 0x001D29A0  size 40 (core 40)
// Second call takes NO arguments (target does not reload a0 before the tail jump).
extern void FUN_001c7ac0(char *p);
extern void FUN_001c7ad8(void);

void FUN_001d29a0(char *p)
{
    FUN_001c7ac0(p);
    *p = 0;
    FUN_001c7ad8();
}
