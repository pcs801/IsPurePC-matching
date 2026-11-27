// FUNCTION: SLPM 0x001DB5E8  size 40  core 40
float FUN_001db5e8(float x)
{
    unsigned int i;

    *(float *)&i = x;
    i &= 0x7FFFFFFFu;
    return *(float *)&i;
}
