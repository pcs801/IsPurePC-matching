// FUNCTION: SLPM 0x00104AE8  size 296  core 296
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_A96AD0[];
extern char D_B1EC00[];
extern char D_00257F20[];
extern char D_00257ED0[];
extern void FUN_0010bf68(char *msg);

int FUN_00104ae8(int count, int reg)
{
    unsigned char *map;
    int idx;
    int i;
    unsigned int v;
    int *p;
    int t;

    if (reg == 0xFFFF)
        return 0;
    t = reg >> 12;
    if (t == 0)
        idx = 1;
    else if (t == 1)
        idx = 3;
    else {
        FUN_0010bf68(D_00257F20);
        return 0;
    }
    switch (idx) {
    case 0: map = (unsigned char *)D_A94750; break;
    case 1: map = (unsigned char *)D_A96750; break;
    case 2: map = (unsigned char *)D_A96850; break;
    case 3: map = (unsigned char *)D_A96950; break;
    case 6: map = (unsigned char *)D_A96AD0; idx = 0; break;
    default:
        FUN_0010bf68(D_00257ED0);
        return 0;
    }
    v = reg & 0xFFF;
    if (count > 0) {
        p = (int *)(*(int *)(D_B1EC00 + 4) + idx * 4);
        for (i = count; i != 0; i--) {
            v += *p;
            p = (int *)((char *)p + 0x14);
        }
    }
    return (map[v >> 3] >> (v & 7)) & 1;
}