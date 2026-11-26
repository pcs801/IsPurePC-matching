// FUNCTION: SLPM 0x00105060  size 112
extern char D_00A98AD0[];

void FUN_00105060(int p, int v)
{
    if (!v)
        *(unsigned char *)((char *)D_00A98AD0 + (((unsigned)(p & 4095) >> 3))) &= ~(1 << ((p & 4095) - (((unsigned)(p & 4095) >> 3) << 3)));
    else
        *(unsigned char *)((char *)D_00A98AD0 + (((unsigned)(p & 4095) >> 3))) |= 1 << ((p & 4095) - (((unsigned)(p & 4095) >> 3) << 3));
}
