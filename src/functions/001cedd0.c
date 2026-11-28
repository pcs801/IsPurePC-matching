// FUNCTION: SLPM 0x001cedd0  size 120  core 120
int FUN_001cedd0(char *p, int size, char *out1, char *out2)
{
    unsigned short h;
    int v;

    if (size < 0x14)
        return -1;
    h = *(unsigned short *)p;
    h = (unsigned short)((h << 8) | (h >> 8));
    if (h != 0x8000)
        return -2;
    v = (*(unsigned short *)(p + 2) << 8) & 0xFFFFFF00;
    v |= *(unsigned char *)(p + 3);
    if ((short)v < 0x10)
        return -1;
    *out1 = *(unsigned char *)(p + 0x12);
    *out2 = *(unsigned char *)(p + 0x13);
    return 0;
}
