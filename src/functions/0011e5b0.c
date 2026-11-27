extern int FUN_0017f518(int a0);
extern void FUN_0017f468(int a0, int a1, int a2);
extern void FUN_00117dc0(int a0);
extern int D_00270CAC;
extern int D_002140F8[];

int FUN_0011e5b0(int self)
{
    short st;
    unsigned short v;
    int *p;
    int adv;
    int idx;

    st = *(short *)(self + 0x10);
    if (st == 0) {
        if (FUN_0017f518(D_00270CAC + 0x4C750) == 1) {
            p = *(int **)(self + 0x44);
            adv = *(int *)(p + 8) + 4;
            FUN_00117dc0(self);
            *(int *)(p + 8) = adv;
            return 0;
        }
        if (*(unsigned char *)(D_00270CAC + 0x47C) != 1) {
            *(char *)(self + 0xD) = 0;
            return 0;
        }
        v = *(unsigned short *)(D_00270CAC + 0x4C74E);
        if (v & 0x80) {
            idx = (v & 0x7F) * 12;
            if (D_002140F8[idx / 4] != *(unsigned char *)(D_00270CAC + 0x47C))
                FUN_0017f468(D_00270CAC + 0x4C750, 0x13, 1);
            else
                FUN_0017f468(D_00270CAC + 0x4C750, 0x23, 1);
        } else {
            FUN_0017f468(D_00270CAC + 0x4C750, 0, 1);
        }
        *(short *)(self + 0x10) = 1;
        *(char *)(self + 0xD) = 0;
        return 0;
    }
    if (st == 1) {
        if (FUN_0017f518(D_00270CAC + 0x4C750) == 1) {
            p = *(int **)(self + 0x44);
            adv = *(int *)(p + 8) + 4;
            FUN_00117dc0(self);
            *(int *)(p + 8) = adv;
            return 0;
        }
        *(char *)(self + 0xD) = 0;
        return 0;
    }
    *(char *)(self + 0xD) = 0;
    return 0;
}
