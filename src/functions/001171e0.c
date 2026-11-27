extern int FUN_00105060(int a0);
extern int FUN_00117270(int a0);
extern int FUN_001174b8(int a0);
extern char D_B1EC00[];

int FUN_001171e0(int a0)
{
    return FUN_00105060(a0);
}

int FUN_001171f8(void)
{
    int i;
    int total;
    int n;

    total = 0;
    i = 0;
    n = *(int *)(D_B1EC00 + 0x20);
    if (total < n) {
        do {
            total += FUN_00117270(i);
            i++;
        } while (i < n);
    }
    if (total < n)
        return 0;
    FUN_001174b8(3);
    return 1;
}
