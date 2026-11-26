// FUNCTION: SLPM 0x00105300
extern char D_00A98C90[];

void FUN_00105300(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_00A98C90 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_00A98C90 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
}
