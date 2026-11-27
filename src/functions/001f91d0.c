unsigned char *FUN_001f91d0(unsigned char *p, unsigned int *out)
{
    unsigned char c;
    unsigned int shift;
    unsigned int val;

    shift = 0;
    val = 0;
    do {
        c = *p++;
        val |= (unsigned int)(c & 0x7F) << shift;
        shift += 7;
    } while (c & 0x80);
    if (shift < 0x20 && (c & 0x40))
        val |= 0xFFFFFFFFu << shift;
    *out = val;
    return p;
}
