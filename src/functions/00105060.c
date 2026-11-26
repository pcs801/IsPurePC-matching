// FUNCTION: SLPM 0x00105060
extern char D_00A98AD0[];

void FUN_00105060(int p, int v)
{
    unsigned int m = p & 4095;
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98AD0 + (m >> 3);
        *q &= ~(1 << (m - ((m >> 3) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98AD0 + (m >> 3);
        *q |= 1 << (m - ((m >> 3) << 3));
    }
}
