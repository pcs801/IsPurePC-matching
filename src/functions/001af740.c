// FUNCTION: SLPM 0x001AF740  size 80  core 80
// The symbol region = a tail-call thunk at 0x001AF740 (20 B) + 4-byte pad
// + the A-family wrapper at 0x001AF758 (56 B).
extern int FUN_001b5738(void);
extern void FUN_001af7d0(void);
extern int FUN_001af790(void *p);
extern void FUN_001af7e8(void);

int FUN_001af740(void)
{
    return FUN_001b5738();
}

int FUN_001af758(char *p)
{
    int r;

    FUN_001af7d0();
    r = FUN_001af790(p);
    FUN_001af7e8();
    return r;
}
