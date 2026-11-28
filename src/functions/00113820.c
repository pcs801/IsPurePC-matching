// FUNCTION: SLPM 0x00113820  size 56  core 56
extern int FUN_0020b2c0(int a0);
extern void FUN_001f6150(int a0, int a1, int a2, void *a3);

int FUN_00113820(int *p, int a1, int a2)
{
    int buf[4];

    if (p[0] == 0)
        return FUN_0020b2c0(p[12]);
    FUN_001f6150(a2 >> 11, a1, 1, buf);
    return p[0] << 11;
}
