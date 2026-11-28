extern int FUN_001e97b8(int a0);

int FUN_001ea6d8(int a0, unsigned int a1)
{
    if (a1 < 2) {
        *(int *)(*(int *)(a0 + 0x40) + 0x87C) = a1;
        FUN_001e97b8(*(int *)(a0 + 0x40));
        return 1;
    }
    return -1;
}
