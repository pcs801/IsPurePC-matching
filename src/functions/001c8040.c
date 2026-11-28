// FUNCTION: SLPM 0x001C8040  size 96  core 96
extern void FUN_001c7ac0(void);
extern void FUN_001c80a0(void *p, int a1, int a2, int a3);
extern void FUN_001c7ad8(void);

void FUN_001c8040(char *p, int a1, int a2, int a3)
{
    FUN_001c7ac0();
    FUN_001c80a0(p, a1, a2, a3);
    FUN_001c7ad8();
}
