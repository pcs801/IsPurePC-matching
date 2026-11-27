int FUN_00203a18(unsigned int a0)
{
    int n = 0;

    if ((a0 & 0xFFFF0000) == 0) { n = 16; a0 <<= 16; }
    if ((a0 & 0xFF000000) == 0) { n += 8; a0 <<= 8; }
    if ((a0 & 0xF0000000) == 0) { n += 4; a0 <<= 4; }
    if ((a0 & 0xC0000000) == 0) { n += 2; a0 <<= 2; }
    if ((int)a0 < 0)
        return n;
    n++;
    if (!(a0 & 0x40000000))
        return 32;
    return n;
}