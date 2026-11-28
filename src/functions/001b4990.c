// FUNCTION: SLPM 0x001B4990  size 64  core 60
// FUN_001b5c28(p); FUN_001b4920(p); *(int*)(p+0x60) = 0xFFFFF; FUN_001b5c40(); return 1;
// the third call sets no arguments (a0 is whatever the second call left).
extern void FUN_001b5c28(char *);
extern void FUN_001b4920(char *);
extern void FUN_001b5c40(void);

int FUN_001b4990(char *p)
{
    FUN_001b5c28(p);
    FUN_001b4920(p);
    *(int *)(p + 0x60) = 0xFFFFF;
    FUN_001b5c40();
    return 1;
}
