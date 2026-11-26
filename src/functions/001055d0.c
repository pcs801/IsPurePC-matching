// FUNCTION: SLPM 0x001055D0  size 144
extern char D_A98D00[];

void FUN_001055D0(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_A98D00 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_A98D00 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
}
