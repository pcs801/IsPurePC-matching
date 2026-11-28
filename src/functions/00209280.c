extern int FUN_00208c78(int a0, char *p, int a2, int a3, int a4, int a5);

int FUN_00209280(int a0, int a1, int a2, char *p)
{
    if (FUN_00208c78(0x80000008, p, 64, *(int *)(p + 0x24), *(int *)(p + 0x28), *(int *)(p + 0x2C)) != 0)
        return 0;
    return 2048;
}
