extern char *FUN_00203708(int a0, int a1);

int FUN_00203b58(int a, int b)
{
    char *p = FUN_00203708(a, 1);

    *(int *)(p + 0x14) = b;
    *(int *)(p + 0x10) = 1;
}
