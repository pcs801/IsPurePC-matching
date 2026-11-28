// FUNCTION: SLPM 0x001C8A10  size 48  core 44
// s0 = p; FUN_001c7ac0(p); FUN_001c8a40(p); tail-call FUN_001c7ad8()
extern void FUN_001c7ac0(char *);
extern void FUN_001c8a40(char *);
extern void FUN_001c7ad8(void);

void FUN_001c8a10(char *p)
{
    FUN_001c7ac0(p);
    FUN_001c8a40(p);
    FUN_001c7ad8();
}
