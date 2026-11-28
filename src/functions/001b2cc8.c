// FUNCTION: SLPM 0x001B2CC8  size 48 core 44
extern void FUN_001cc5b0(int);
extern void FUN_001cc358(int);

void FUN_001b2cc8(char *p)
{
    FUN_001cc5b0(*(int *)(p + 4));
    FUN_001cc358(*(int *)(p + 4));
}
