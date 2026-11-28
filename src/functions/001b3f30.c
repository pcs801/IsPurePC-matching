extern int FUN_001cd1a8(int a0);
extern int FUN_001cd1b0(int a0);

int FUN_001b3f30(int a0)
{
    if (FUN_001cd1a8(*(int *)(a0 + 4)) <= 0)
        return 0;
    if ((unsigned int)(*(unsigned char *)(a0 + 1) - 2) >= 2)
        return 0;
    return FUN_001cd1b0(*(int *)(a0 + 4));
}
