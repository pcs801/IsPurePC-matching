// FUNCTION: SLPM 0x001C9560  size 48  core 44
// s0 = p; FUN_001c7ac0(p); FUN_001c9590(p); tail-call FUN_001c7ad8()
extern void FUN_001c7ac0(char *);
extern void FUN_001c9590(char *);
extern void FUN_001c7ad8(void);

void FUN_001c9560(char *p)
{
    FUN_001c7ac0(p);
    FUN_001c9590(p);
    FUN_001c7ad8();
}
