// FUNCTION: SLPM 0x001B8D20  size 48  core 44  (skeleton A)
extern void FUN_001ce9b8(char *);
extern int FUN_001b8d58(char *);
extern void FUN_001ce9c0(void);

int FUN_001b8d20(char *p)
{
    int r;

    FUN_001ce9b8(p);
    r = FUN_001b8d58(p);
    FUN_001ce9c0();
    return r;
}
