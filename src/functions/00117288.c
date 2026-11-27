extern int FUN_00105238(void);
extern int FUN_00117270(int a0);
extern int FUN_001174b8(int a0);
extern char D_B1EC00[];

int FUN_00117288(void)
{
    int i;
    int cnt;
    int n;

    i = 0;
    cnt = 0;
    FUN_00105238();
    n = *(int *)(D_B1EC00 + 0x20);
    for (; cnt < n; ) {
        cnt += FUN_00117270(i);
        i++;
        if (i >= n)
            break;
    }
    if (cnt < n)
        return 1;
    return FUN_001174b8(3);
}
