// FUNCTION: SLPM 0x00105698  size 144
// note: same shape as 0x001055D0 (unmasked bit index -> signed division p / 8).
extern char D_A98D10[];

void FUN_00105698(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_A98D10 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_A98D10 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
}
