// FUNCTION: SLPM 0x001B4088  size 32  core 32 (region = wrapper + setter at 0x1B40A0)
extern void FUN_001cd210(int);

void FUN_001b4088(char *p)
{
    FUN_001cd210(*(int *)(p + 4));
}

void FUN_001b40a0(char *p, int v)
{
    *(int *)(p + 168) = v;
}
