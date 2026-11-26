// FUNCTION: SLPM 0x001050F8
extern char D_00A98BD0[];

void FUN_001050f8(int p, int v)
{
    unsigned int m = p & 4095;
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98BD0 + (m >> 3);
        *q &= ~(1 << (m - ((m >> 3) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98BD0 + (m >> 3);
        *q |= 1 << (m - ((m >> 3) << 3));
    }
}
