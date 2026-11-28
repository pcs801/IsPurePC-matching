// FUNCTION: SLPM 0x001B7278  size 80  core 80
extern void FUN_001ce9b8(void);
extern void FUN_001b72c8(void *p, int v, int w);
extern void FUN_001ce9c0(void);

void FUN_001b7278(char *p, int v, int w)
{
    FUN_001ce9b8();
    FUN_001b72c8(p, v, w);
    FUN_001ce9c0();
}
