int FUN_001c8ac0(char *p, int a1)
{
    if (a1 == 1)
        return *(int *)(p + 0xC);
    if (a1 == 0)
        return *(int *)(p + 0x10);
    if (*(int (**)(int, int))(p + 0x38) != 0)
        (*(int (**)(int, int))(p + 0x38))(*(int *)(p + 0x3C), -3);
    return 0;
}
