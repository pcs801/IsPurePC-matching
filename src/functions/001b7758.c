// FUNCTION: SLPM 0x001B7758  size 64  core 64
extern void FUN_001ce9b8(void);
extern int FUN_001b7790(void *p);
extern void FUN_001ce9c0(void);

int FUN_001b7758(char *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b7790(p);
    FUN_001ce9c0();
    return r;
}
