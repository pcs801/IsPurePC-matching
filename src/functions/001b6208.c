extern int FUN_001c35c8(int a0, int a1, int a2, int a3);

int FUN_001b6208(int a0)
{
    if (a0 != 0)
        return FUN_001c35c8(*(int *)(a0), *(int *)(a0 + 8), *(int *)(a0 + 0xC), *(int *)(a0 + 4));
    return 0;
}
