// FUNCTION: SLPM 0x001B92A8  size 48  core 44  (skeleton A)
// r = MID(p) kept in a local; FUN_001ce9c0 takes no argument (a0 stays p)
extern void FUN_001ce9b8(char *);
extern int FUN_001b92e0(char *);
extern void FUN_001ce9c0(void);

int FUN_001b92a8(char *p)
{
    int r;

    FUN_001ce9b8(p);
    r = FUN_001b92e0(p);
    FUN_001ce9c0();
    return r;
}
