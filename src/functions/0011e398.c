extern int FUN_0017f4e8(int a0, int a1, int a2, int a3);
extern int FUN_00115730(int a0);
extern void FUN_0017f468(int a0, int a1);
extern void FUN_00109568(int a0);
extern void FUN_0017e488(int a0);
extern void FUN_00117dc0(int a0);
extern int D_00270CAC;
extern int D_002140F0[];
extern int D_002140F4[];

int FUN_0011e398(int self)
{
    int *p;
    int rec;
    unsigned short v;
    int c;
    int r;
    int k;
    int idx;
    int off;

    p = *(int **)(self + 0x44);
    rec = *(int *)(p + 8);
    v = *(unsigned short *)(rec + 4);
    if ((v & 0xF000) == 0)
        *(unsigned short *)(D_00270CAC + 0x4C74C) = v;
    c = *(unsigned short *)(D_00270CAC + 0x4C74C) & 0xFFF;
    if (c == 0xFFF)
        FUN_0017f4e8(D_00270CAC + 0x4C750, 0xFF, 0xFF, 0xFF);
    else
        FUN_0017f4e8(D_00270CAC + 0x4C750, (c >> 8) << 4, c & 0xF0, (c & 0xF) << 4);
    r = FUN_00115730(*(short *)(rec + 2));
    k = *(unsigned char *)(rec + 1);
    r = r > 0 ? 1 : r;
    if (k != 0x7F) {
        *(unsigned short *)(D_00270CAC + 0x4C74E) = k;
    } else {
        v = *(unsigned short *)(D_00270CAC + 0x4C74E);
        *(unsigned short *)(D_00270CAC + 0x4C74E) = (k & 0x80) | (v & 0x7F);
    }
    v = *(unsigned short *)(D_00270CAC + 0x4C74E);
    idx = v & 0x7F;
    off = idx * 12;
    if (v & 0x80)
        FUN_0017f468(D_00270CAC + 0x4C750, D_002140F4[off / 4]);
    else
        FUN_0017f468(D_00270CAC + 0x4C750, D_002140F0[off / 4]);
    off = D_002140F0[idx * 3 + 2];
    if (off == 1)
        FUN_00109568(r);
    else if (off == 2)
        FUN_0017e488(r);
    p = *(int **)(self + 0x44);
    p[8] = p[8] + 8;
    FUN_00117dc0(self);
    return 0;
}
