// FUNCTION: SLPM 0x001B6ED0  size 48  core 44
// s0 = p; FUN_001ce9b8(p); FUN_001b6f00(p); tail-call FUN_001ce9c0()
extern void FUN_001ce9b8(char *);
extern void FUN_001b6f00(char *);
extern void FUN_001ce9c0(void);

void FUN_001b6ed0(char *p)
{
    FUN_001ce9b8(p);
    FUN_001b6f00(p);
    FUN_001ce9c0();
}
