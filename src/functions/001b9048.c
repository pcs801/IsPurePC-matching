// FUNCTION: SLPM 0x001B9048  size 80  core 80
extern void FUN_001ce9b8(void);
extern void FUN_001b90a0(void *p, int v, int w);
extern void FUN_001ce9c0(void);

void FUN_001b9048(char *p, int v, int w)
{
    FUN_001ce9b8();
    FUN_001b90a0(p, v, w);
    FUN_001ce9c0();
}
