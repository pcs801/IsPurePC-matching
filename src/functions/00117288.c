extern int FUN_00105238(void);
extern int FUN_00117270(int a0);
extern int FUN_001174b8(int a0);
extern char D_B1EC00[];

int FUN_00117288(void)
{
    int i;
    int total;
    int n;

    i = 0;
    total = 0;
    FUN_00105238();
    n = *(int *)(D_B1EC00 + 0x20);
    if (total < n) {
        do {
            total += FUN_00117270(i);
            i++;
        } while (i < n);
    }
    if (total < n)
        return 1;
    return FUN_001174b8(3);
}
