// FUNCTION: SLPM 0x001AF660  size 48  core 44
// if (p == 0) return 0; if (*(int*)(p+4) == 0) return 0; return FUN_001b5be8(*(int*)(p+4));
extern int FUN_001b5be8(int);

int FUN_001af660(char *p)
{
    if (p == 0)
        return 0;
    if (*(int *)(p + 4) == 0)
        return 0;
    return FUN_001b5be8(*(int *)(p + 4));
}
