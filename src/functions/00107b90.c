// FUNCTION: SLPM 0x00107B90
extern unsigned char D_281580[];
extern int FUN_00105b90(int);
extern float FUN_001d83b0(float);
extern void FUN_001b7da8(int, int);

void FUN_00107b90(int idx, short v)
{
    unsigned char *p;
    int vol;

    if (v >= 0)
        D_281580[idx * 0x4E280 + 1] = v;
    p = D_281580 + idx * 0x4E280;
    if (p[3] != 0) {
        int t;
        vol = -999;
        t = FUN_00105b90(p[2]) * p[1] / 128;
        if (t != 0)
            vol = (int)(-FUN_001d83b0(1.0f / ((float)t * 0.0078125f)) * 20.0f * 10.0f);
        FUN_001b7da8(*(int *)(p + 4), vol);
    }
}

// FUNCTION: SLPM 0x00107C98
unsigned char FUN_00107c98(int idx)
{
    return D_281580[idx * 0x4E280 + 1];
}
