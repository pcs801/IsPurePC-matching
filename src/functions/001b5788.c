// FUNCTION: SLPM 0x001B5788  size 64  core 64
extern void FUN_001b5c70(void *p);
extern int FUN_001b57c0(void *p);
extern void FUN_001b5c88(void);

int FUN_001b5788(char *p)
{
    int r;

    FUN_001b5c70(p);
    r = FUN_001b57c0(p);
    FUN_001b5c88();
    return r;
}
