// FUNCTION: SLPM 0x001e0180  size 88  core 88
void FUN_001e0180(char *a0, short *a1)
{
    *(long long *)(a0 + 0x00) = ((long long)a1[0] << 32) | ((long long)a1[1] << 48) |
                                ((long long)a1[2] << 56);
    *(long long *)(a0 + 0x10) = ((long long)a1[3] << 32) | ((long long)a1[4] << 48);
    *(long long *)(a0 + 0x20) = (long long)a1[5] | ((long long)a1[6] << 32);
    *(long long *)(a0 + 0x30) = 0;
}
