extern int FUN_001e0f50(int a0);

void FUN_001e0e60(int a0)
{
    int s0;

    s0 = a0;
    FUN_001e0f50(a0);
    *(long long *)(s0 + 0x50) = 0;
    *(long long *)(s0 + 0x40) = 0x810000807F;
    *(long long *)(s0 + 0x30) = 0;
}
