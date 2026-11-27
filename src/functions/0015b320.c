extern char *D_00270BE0;
extern int FUN_0015ab98(void);
extern int FUN_0015aee8(void);
extern int FUN_0015b060(void);
extern int FUN_0015ac90(void);
extern int FUN_0015adf0(void);

int FUN_0015b320(int stage, int flag)
{
    char *g;
    int i;
    int n;
    int cnt;
    int tmp;
    signed char sub;

    g = D_00270BE0;
    *(int *)(g + 0x4C8) = stage;
    *(int *)(g + 0x4CC) = flag;
    if (stage == 0) {
        n = *(int *)(g + 0xC0);
        for (i = 0; i < n; i++)
            *(int *)(g + 0xC8 + i * 4) = i;
        *(int *)(g + 0x4D4) = n;
    } else if (stage == 1) {
        n = *(int *)(g + 0xC0);
        cnt = 0;
        for (i = 0; i < n; i++) {
            if (*(signed char *)(*(int *)(g + 0xBC) + i * 32 + 5) == 0) {
                *(int *)(g + 0xC8 + cnt * 4) = i;
                cnt++;
            }
        }
        *(int *)(g + 0x4D4) = cnt;
    } else if (stage == 2) {
        sub = *(signed char *)(g + 0x5C);
        *(int *)(g + 0x4D0) = sub;
        if ((unsigned char)sub < 6) {
            switch (sub) {
            case 0:
            case 1:
                FUN_0015ab98();
                break;
            case 2:
                FUN_0015aee8();
                break;
            case 3:
                FUN_0015b060();
                break;
            case 4:
                FUN_0015ac90();
                break;
            case 5:
                FUN_0015adf0();
                break;
            }
        }
    } else {
        return 1;
    }
    if (flag == 1) {
        n = *(int *)(g + 0x4D4);
        for (i = 0; i < n / 2; i++) {
            tmp = *(int *)(g + 0xC8 + i * 4);
            *(int *)(g + 0xC8 + i * 4) = *(int *)(g + 0xC8 + (n - 1 - i) * 4);
            *(int *)(g + 0xC8 + (n - 1 - i) * 4) = tmp;
        }
    }
    return 1;
}
