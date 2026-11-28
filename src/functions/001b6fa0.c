// FUNCTION: SLPM 0x001B6FA0  size 48  core 44
// s0 = p; FUN_001ce9b8(p); FUN_001b6fd0(p); tail-call FUN_001ce9c0()
extern void FUN_001ce9b8(char *);
extern void FUN_001b6fd0(char *);
extern void FUN_001ce9c0(void);

void FUN_001b6fa0(char *p)
{
    FUN_001ce9b8(p);
    FUN_001b6fd0(p);
    FUN_001ce9c0();
}
