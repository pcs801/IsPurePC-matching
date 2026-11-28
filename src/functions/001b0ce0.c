// FUNCTION: SLPM 0x001B0CE0  size 96  core 80
// if (p == 0) return; FUN_002058a0(p, &b); if (b == 8 || b == 0xC) FUN_00206868(p);
// (sibling of 0x1B0C28/0x1B0C78 from t455 - same guard with a different compare constant)
extern void FUN_002058a0(char *, int *);
extern void FUN_00206868(char *);

void FUN_001b0ce0(char *p)
{
    int b;

    if (p == 0)
        return;
    FUN_002058a0(p, &b);
    if (b == 8 || b == 0xC)
        FUN_00206868(p);
}
