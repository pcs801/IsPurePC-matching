extern unsigned char D_270E80[];
extern int FUN_00105b90(int);
extern int FUN_00107b20(int);
extern void FUN_001b7da8(int, int);

void FUN_00107758(int v)
{
    int n, vol;
    unsigned char *p;

    if (v >= 0)
        D_270E80[0] = v;
    vol = FUN_00107b20(FUN_00105b90(D_270E80[1]) * D_270E80[0] / 128);
    p = D_270E80 + 0x84;
    for (n = 3; n >= 0; n--) {
        FUN_001b7da8(*(int *)p, vol);
        p += 0x4180;
    }
}

void FUN_001077f0(int v)
{
    D_270E80[1] = v;
}
