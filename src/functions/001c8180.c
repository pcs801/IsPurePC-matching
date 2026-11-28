// FUNCTION: SLPM 0x001C8180  size 80  core 76
extern void FUN_001c7ac0(void);
extern void FUN_001c81d0(void *p, int v, int w);
extern void FUN_001c7ad8(void);

void FUN_001c8180(char *p, int v, int w)
{
    FUN_001c7ac0();
    FUN_001c81d0(p, v, w);
    FUN_001c7ad8();
}
