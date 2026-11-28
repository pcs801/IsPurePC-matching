// FUNCTION: SLPM 0x001C9F28  size 72  core 72
extern void FUN_001c7ac0(void);
extern int FUN_001c9f70(char *p, int v);
extern void FUN_001c7ad8(void);

int FUN_001c9f28(char *p, int v)
{
    int r;

    FUN_001c7ac0();
    r = FUN_001c9f70(p, v);
    FUN_001c7ad8();
    return r;
}
