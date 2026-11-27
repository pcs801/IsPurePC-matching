// FUNCTION: SLPM 0x001CC468  size 136 (core 136)
// Returns 1 when one of the four (11,119)/(119,11) byte-pair combinations matches, else 0.
int FUN_001cc468(unsigned char *p)
{
    if (p[0] == 11 && p[1] == 119)
        return 1;
    if (p[0] == 119 && p[1] == 11)
        return 1;
    if (p[0x10] == 11 && p[0x11] == 119)
        return 1;
    if (p[0x10] == 119 && p[0x11] == 11)
        return 1;
    return 0;
}
