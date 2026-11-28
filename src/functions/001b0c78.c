// FUNCTION: SLPM 0x001B0C78  size 96  core 80
// if (p == 0) return; FUN_002058a0(p, &b); if (b == 4 || b == 0xC) FUN_00206868(p);
extern void FUN_002058a0(char *, int *);
extern void FUN_00206868(char *);

void FUN_001b0c78(char *p)
{
    int b;

    if (p == 0)
        return;
    FUN_002058a0(p, &b);
    if (b == 4 || b == 0xC)
        FUN_00206868(p);
}
