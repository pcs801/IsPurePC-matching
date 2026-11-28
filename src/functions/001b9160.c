// FUNCTION: SLPM 0x001B9160  size 96  core 96
// Region = tail thunk (20 B) + pad + three-call wrapper at 0x001B9178 (72 B).
extern void FUN_001cf5f0(void);
extern void FUN_001ce9b8(void);
extern int FUN_001b91c0(void *p, int v);
extern void FUN_001ce9c0(void);

void FUN_001b9160(void)
{
    FUN_001cf5f0();
}

int FUN_001b9178(char *p, int v)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b91c0(p, v);
    FUN_001ce9c0();
    return r;
}
