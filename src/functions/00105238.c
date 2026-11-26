// FUNCTION: SLPM 0x00105238
extern char D_00A98C50[];

void FUN_00105238(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98C50 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98C50 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
}
