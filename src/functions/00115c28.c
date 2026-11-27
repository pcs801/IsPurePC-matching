// FUNCTION: SLPM 0x00115C28
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_00259650[];
extern char D_00259680[];
extern int D_00B1EC04;
extern int FUN_0010bf68(char *);

void FUN_00115c28(int cnt, int index)
{
    char *table;
    int b;
    int *p;

    index &= 0xFFFF;
    if (index == 0xFFFF)
        return;
    switch ((unsigned int)index >> 12) {
    case 0:
        b = 0;
        break;
    case 1:
        b = 2;
        break;
    default:
        return (void)FUN_0010bf68(D_00259680);
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
        table = 0;
        return;
    }
    if (cnt > 0) {
        p = (int *)(b * 4 + D_00B1EC04);
        do {
            index += *p;
            p += 5;
            cnt--;
        } while (cnt != 0);
    }
    {
        unsigned char mask = 1 << (index & 7);
        ((unsigned char *)table)[(unsigned int)index >> 3] |= mask;
    }
}
