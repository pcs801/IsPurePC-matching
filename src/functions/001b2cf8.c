// FUNCTION: SLPM 0x001B2CF8  size 48  core 44
// s0 = p; FUN_001b2a20(p); *(char*)(p+1) = 1
extern void FUN_001b2a20(char *);

void FUN_001b2cf8(char *p)
{
    FUN_001b2a20(p);
    *(char *)(p + 1) = 1;
}
