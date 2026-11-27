// FUNCTION: SLPM 0x00115D38
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_00259650[];
extern char D_00259668[];
extern int D_00B1EC04;
extern int FUN_0010bf68(char *);

int FUN_00115d38(int cnt, int index)
{
    char *table;
    int b;
    int *p;

    index &= 0xFFFF;
    if (index == 0xFFFF)
        return 0;
    switch ((unsigned int)index >> 12) {
    case 0:
        b = 1;
        break;
    case 1:
        b = 3;
        break;
    default:
        FUN_0010bf68(D_00259668);
        return 0;
    }
    index &= 0xFFF;
    switch (b) {
    case 0:
        table = D_A94750;
        break;
    case 1:
        table = D_A96750;
        break;
    case 2:
        table = D_A96850;
        break;
    case 3:
        table = D_A96950;
        break;
    default:
        FUN_0010bf68(D_00259650);
        return 0;
    }
    if (cnt > 0) {
        p = (int *)(b * 4 + D_00B1EC04);
        do {
            index += *p;
            p += 5;
            cnt--;
        } while (cnt != 0);
    }
    return (((unsigned char *)table)[(unsigned int)index >> 3] >> (index & 7)) & 1;
}
