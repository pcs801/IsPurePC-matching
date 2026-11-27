// FUNCTION: SLPM 0x00115B20
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_00259650[];
extern char D_00259668[];
extern int D_00B1EC04;
extern int FUN_0010bf68(char *);

int FUN_00115b20(int cnt, int index)
{
    unsigned int idx = index & 0xFFFF;
    char *table;
    int b;
    int *p;

    if (idx == 0xFFFF)
        return 0;
    switch (idx >> 12) {
    case 0:
        b = 0;
        break;
    case 1:
        b = 2;
        break;
    default:
        FUN_0010bf68(D_00259668);
        return 0;
    }
    idx &= 0xFFF;
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
            idx += *p;
            p += 5;
            cnt--;
        } while (cnt != 0);
    }
    return (((unsigned char *)table)[idx >> 3] >> (idx & 7)) & 1;
}
