// FUNCTION: SLPM 0x00105168  size 152
extern char D_00A98B50[];

int FUN_00105168(int p)
{
    return ((*(unsigned char *)((char *)D_00A98B50 + (((unsigned)(p & 4095) >> 3))) >> ((p & 4095) - (((unsigned)(p & 4095) >> 3) << 3))) & 1);
}

static void FUN_00105190(int p, int v)
{
    unsigned int m = p & 4095;
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98B50 + (m >> 3);
        *q &= ~(1 << (m - ((m >> 3) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98B50 + (m >> 3);
        *q |= 1 << (m - ((m >> 3) << 3));
    }
}
