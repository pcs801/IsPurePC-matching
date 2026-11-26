// FUNCTION: SLPM 0x00105508  size 144
extern char D_A98CF0[];

void FUN_00105508(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_A98CF0 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_A98CF0 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
}
