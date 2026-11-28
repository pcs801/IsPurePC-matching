// FUNCTION: SLPM 0x001B77E0  size 64  core 64
extern void FUN_001ce9b8(void);
extern int FUN_001b7818(void *p);
extern void FUN_001ce9c0(void);

int FUN_001b77e0(char *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b7818(p);
    FUN_001ce9c0();
    return r;
}
