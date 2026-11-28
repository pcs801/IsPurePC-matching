// FUNCTION: SLPM 0x001B0C28  size 96  core 80
// if (p == 0) return; FUN_002058b0(p, &b); if (b == 4 || b == 0xC) FUN_00206868(p);
extern void FUN_002058b0(char *, int *);
extern void FUN_00206868(char *);

void FUN_001b0c28(char *p)
{
    int b;

    if (p == 0)
        return;
    FUN_002058b0(p, &b);
    if (b == 4 || b == 0xC)
        FUN_00206868(p);
}
