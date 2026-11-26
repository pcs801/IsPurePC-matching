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
    int v;

    if (p[3] != 0) {
        FUN_001b7da8(*(int *)(p + 4), 0);
        FUN_001b6fa0(*(int *)(p + 4));
    }
    p[3] = 1;
    FUN_001b9b98(*(int *)(p + 4), p[0], a1);
    if (p[3] == 0)
        return;
    v = FUN_00105b90(p[2]) * p[1] / 128;
    FUN_001b7da8(*(int *)(p + 4),
                 v != 0 ? (int)(-FUN_001d83b0(1.0f / ((float)v * 0.0078125f)) * 20.0f * 10.0f) : -999);
}
