extern int FUN_00209140(int a0);

int FUN_00209170(int a0, int a1)
{
    if (a1 < 0 || a1 >= *(int *)(a0 + 0x20)) {
        FUN_00209140(a0);
        return 0;
    }
    return *(int *)(*(int *)(a0 + 0x1C) + a1 * 64);
}
