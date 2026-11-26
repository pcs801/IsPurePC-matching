// FUNCTION: SLPM 0x001AF7A8
int FUN_001af7a8(int a0)
{
    int q = a0;
    if (a0 < 0)
        q = a0 + 0x7FF;
    q >>= 11;
    q += (a0 - (q << 11)) > 0;
    return q;
}
