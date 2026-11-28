// FUNCTION: SLPM 0x001B3EB8  size 48 core 44
extern int FUN_001cd180(int);

int FUN_001b3eb8(char *p)
{
    if (p == 0)
        return 0;
    return FUN_001cd180(*(int *)(p + 4));
}
