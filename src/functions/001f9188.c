unsigned char *FUN_001f9188(unsigned char *p, int *out)
{
    unsigned char c;
    int val;
    int shift;

    c = *p++;
    shift = 0;
    val = c & 0x7F;
    if (c & 0x80) {
        do {
            c = *p++;
            shift += 7;
            val |= (c & 0x7F) << shift;
        } while (c & 0x80);
    }
    *out = val;
    return p;
}
