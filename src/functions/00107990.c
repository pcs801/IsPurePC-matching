extern unsigned char D_270E80[];
extern int FUN_00105b90(int);
extern int FUN_0010bd80(int, int);

int FUN_00107990(short v)
{
    int a, b;

    if (v >= 0)
        D_270E80[0x10680] = v;
    a = FUN_00105b90(D_270E80[0x10681]);
    b = D_270E80[0x10680];
    return FUN_0010bd80(0xD1, (int)((float)(a * b / 128) / 128.0f * 256.0f));
}
