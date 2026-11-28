// FUNCTION: SLPM 0x001B58A0  size 72  core 72
extern void FUN_001b5c70(void);
extern int FUN_001b58e8(void *p, int v);
extern void FUN_001b5c88(void);

int FUN_001b58a0(char *p, int v)
{
    int r;

    FUN_001b5c70();
    r = FUN_001b58e8(p, v);
    FUN_001b5c88();
    return r;
}
