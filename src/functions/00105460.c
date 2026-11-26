// FUNCTION: SLPM 0x00105460  size 112
extern char D_00A98CE0[];

void FUN_00105460(int p, int v)
{
    int m = (p & 4095) >> 1;
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98CE0 + ((unsigned)m >> 3);
        *q &= ~(1 << (m - (((unsigned)m >> 3) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98CE0 + ((unsigned)m >> 3);
        *q |= 1 << (m - (((unsigned)m >> 3) << 3));
    }
}
