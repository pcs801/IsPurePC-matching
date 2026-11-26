// FUNCTION: SLPM 0x001053C0
extern char D_00A98CD0[];

void FUN_001053c0(int p, int v)
{
    int m = (p & 4095) >> 1;
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98CD0 + ((unsigned)m >> 3);
        *q &= ~(1 << (m - (((unsigned)m >> 3) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98CD0 + ((unsigned)m >> 3);
        *q |= 1 << (m - (((unsigned)m >> 3) << 3));
    }
}
