// FUNCTION: SLPM 0x001B7978  size 64  core 64
extern void FUN_001ce9b8(void);
extern int FUN_001b79b0(void *p);
extern void FUN_001ce9c0(void);

int FUN_001b7978(char *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b79b0(p);
    FUN_001ce9c0();
    return r;
}
