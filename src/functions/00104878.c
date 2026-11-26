// FUNCTION: SLPM 0x00104878  size 328  core 324
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_B1EC00[];
extern char D_00257EB8[];
extern void FUN_0010bf68(char *msg);

int FUN_00104878(int idx)
{
    unsigned char *map;
    int *st;
    unsigned int n;
    unsigned int i;
    int total;
    int pos;
    int end;
    int k;
    int *p;
    unsigned short *q;

    switch (idx) {
    case 0: map = (unsigned char *)D_A94750; break;
    case 1: map = (unsigned char *)D_A96750; break;
    case 2: map = (unsigned char *)D_A96850; break;
    case 3: map = (unsigned char *)D_A96950; break;
    default:
        FUN_0010bf68(D_00257EB8);
        return 0;
    }
    st = (int *)D_B1EC00;
    n = *(unsigned int *)((char *)st + 0x50);
    total = 0;
    p = (int *)(*(int *)((char *)st + 4) + idx * 4);
    q = (unsigned short *)*(int *)((char *)st + 0x68A8);
    pos = 0;
    for (i = 0; i < n; i++) {
        end = pos + *p;
        if (*q != 0xFFFF) {
            for (k = pos; k < end; k++)
                total += (map[k / 8] >> (k % 8)) & 1;
        }
        pos = end;
        q++;
        p += 5;
    }
    return total;
}