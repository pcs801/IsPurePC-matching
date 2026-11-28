// FUNCTION: SLPM 0x001B4A18  size 72  core 72
extern void FUN_001b5c28(void);
extern int FUN_001b4920(void *p);
extern void FUN_001b5c40(void);

int FUN_001b4a18(char *p, int v)
{
    FUN_001b5c28();
    FUN_001b4920(p);
    *(int *)(p + 96) = v;
    FUN_001b5c40();
    return 1;
}
