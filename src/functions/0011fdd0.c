// FUNCTION: SLPM 0x0011FDD0  size 296  core 292
extern int *D_00270CB0;
extern unsigned char *D_00270CAC;
extern unsigned char D_C56500[];
extern void FUN_00106668(int);

int FUN_0011fdd0(void)
{
    unsigned int *p;
    unsigned int st;
    unsigned int k;
    unsigned int v;

    if (D_00270CB0[0x6010 / 4] != 1)
        return 0;
    p = (unsigned int *)D_C56500;
    st = p[2];
    if (st & 0x2000) {
        FUN_00106668(0);
        D_00270CB0[0x6010 / 4] = 2;
        D_00270CAC[0x479] = 7;
        return 1;
    }
    if (st & 0x4000) {
        FUN_00106668(1);
        D_00270CB0[0x6010 / 4] = 0;
        D_00270CAC[0x491] = 0;
        return 1;
    }
    if (st & 1) {
        if (D_00270CB0[0x6014 / 4] == D_00270CB0[0x6018 / 4] - 1) {
            FUN_00106668(1);
            D_00270CB0[0x6010 / 4] = 0;
            D_00270CAC[0x491] = 0;
            return 1;
        }
        FUN_00106668(3);
        v = D_00270CB0[0x6014 / 4] + D_00270CB0[0x6018 / 4] + 1;
    } else {
        k = p[4];
        if (k & 0x90) {
            FUN_00106668(3);
            v = D_00270CB0[0x6014 / 4] + D_00270CB0[0x6018 / 4] - 1;
        } else if (k & 0x60) {
            FUN_00106668(3);
            v = D_00270CB0[0x6014 / 4] + D_00270CB0[0x6018 / 4] + 1;
        } else {
            return 1;
        }
    }
    D_00270CB0[0x6014 / 4] = v % D_00270CB0[0x6018 / 4];
    return 1;
}
