// FUNCTION: SLPM 0x00107B20  size 112  core 112

extern float FUN_001d83b0(float);

int FUN_00107b20(int a0)
{
    int v = -999;

    if (a0 != 0)
        v = (int)(-FUN_001d83b0(1.0f / ((float)a0 * 0.0078125f)) * 20.0f * 10.0f);
    return v;
}
