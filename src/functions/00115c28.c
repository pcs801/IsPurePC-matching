// FUNCTION: SLPM 0x00115C28
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_00259650[];
extern char D_00259680[];
extern int D_00B1EC04;
extern int FUN_0010bf68(char *);

int FUN_00115c28(int cnt, unsigned short index)
{
    char *table;
    int b;
    int *p;
    int bit;

    if (index == 0xFFFF)
        return 0xFFFF;
    switch (index >> 12) {
    case 0:
        b = 0;
        break;
    case 1:
        b = 2;
        break;
    default:
        return FUN_0010bf68(D_00259680);
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
        return FUN_0010bf68(D_00259650);
    }
    if (cnt > 0) {
        p = (int *)(b * 4 + D_00B1EC04);
        do {
            index += *p;
            p += 5;
            cnt--;
        } while (cnt != 0);
    }
    bit = 1 << (index & 7);
    ((unsigned char *)table)[index >> 3] |= bit;
    return bit;
}
