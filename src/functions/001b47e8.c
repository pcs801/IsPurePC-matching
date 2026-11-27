// FUNCTION: SLPM 0x001B47E8  size 32  core 28
// lb v1,0x49(a0) / bnez -> return 0 / lb v0,0x4d(a0) / sltu v0,zero,v0
int FUN_001b47e8(char *p)
{
    if (*(signed char *)(p + 0x49) != 0)
        return 0;
    return *(signed char *)(p + 0x4D) != 0;
}
