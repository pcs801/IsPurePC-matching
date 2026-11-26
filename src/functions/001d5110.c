// FUNCTION: SLPM 0x001D5110  size 48 (two 16-bit store helpers, 24 bytes each)
// 0x001D5110: big-endian 16-bit store  -> sb at +1 (low), sb at +0 (high)
// 0x001D5128: little-endian 16-bit store -> sb at +0 (low), sb at +1 (high)
// Both halves sign-extend the incoming int arg to short, so each half is 6 words.
void FUN_001d5110(char *p, int h) {
    short v = (short)h;
    p[1] = (char)v;
    p[0] = (char)((unsigned short)v >> 8);
}

void FUN_001d5128(char *p, int h) {
    short v = (short)h;
    p[0] = (char)v;
    p[1] = (char)((unsigned short)v >> 8);
}
