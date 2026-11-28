// FUNCTION: SLPM 0x001B55C0  size 72  core 72
extern void FUN_001b5c70(void);
extern int FUN_001b5608(void *p, int v);
extern void FUN_001b5c88(void);

int FUN_001b55c0(char *p, int v)
{
    int r;

    FUN_001b5c70();
    r = FUN_001b5608(p, v);
    FUN_001b5c88();
    return r;
}
