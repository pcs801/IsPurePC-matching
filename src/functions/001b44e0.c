// FUNCTION: SLPM 0x001B44E0  size 48  core 44
// s0 = p; FUN_001b5c70(p); FUN_001b4510(p); tail-call FUN_001b5c88()
extern void FUN_001b5c70(char *);
extern void FUN_001b4510(char *);
extern void FUN_001b5c88(void);

void FUN_001b44e0(char *p)
{
    FUN_001b5c70(p);
    FUN_001b4510(p);
    FUN_001b5c88();
}
