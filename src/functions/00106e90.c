// FUNCTION: SLPM 0x00106E90  size 280  core 280
extern unsigned char D_281580[];

extern int FUN_001b7da8(int, int);
extern void FUN_001b6fa0(int);
extern int FUN_001b9b98(int, int, int);
extern int FUN_00105b90(int);
extern float FUN_001d83b0(float);

void FUN_00106e90(int a0, int a1)
{
    unsigned char *p = D_281580 + a0 * 0x4E280;
    int h;
    int v;
    int arg;
    int q;

    if (p[3] != 0) {
        FUN_001b7da8(*(int *)(p + 4), 0);
        FUN_001b6fa0(*(int *)(p + 4));
    }
    h = *(int *)(p + 4);
    p[3] = 1;
    FUN_001b9b98(h, p[0], a1);
    if (p[3] == 0)
        return;
    v = FUN_00105b90(p[2]);
    arg = -999;
    q = v * p[1] / 128;
    if (q != 0)
        arg = (int)(-FUN_001d83b0(1.0f / ((float)q * 0.0078125f)) * 20.0f * 10.0f);
    FUN_001b7da8(*(int *)(p + 4), arg);
}
