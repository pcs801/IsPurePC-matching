// FUNCTION: SLPM 0x001A9C70  size 136 (core 132)
// Validation chain: each failing check returns its own 1-based index, success returns 0.
int FUN_001a9c70(unsigned char *p)
{
    if (p[4] != 1)
        return 1;
    if (p[5] != p[4])
        return 2;
    if (*(unsigned short *)(p + 0x10) != 2)
        return 3;
    if (*(unsigned short *)(p + 0x12) != 8)
        return 4;
    if (*(unsigned short *)(p + 0x28) != 0x34)
        return 5;
    if (*(unsigned short *)(p + 0x2A) != 0x20)
        return 6;
    if (*(unsigned short *)(p + 0x30) != 0) {
        if (*(unsigned short *)(p + 0x2E) != 0x28)
            return 7;
    }
    return 0;
}
