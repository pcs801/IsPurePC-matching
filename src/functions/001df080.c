// FUNCTION: SLPM 0x001DF080  size 96 (core 96)
// NOT COMPLETED: lookup over a counted array at p+0x40 with a count byte at p+0x11 and a
// per-entry 4-byte key; needs the full 24-instruction walk (only the head is transcribed
// here). Returns a byte offset (p + u16 at +0xC) or 0.
int FUN_001df080(char *p, int key)
{
    unsigned char n = *(unsigned char *)(p + 0x11);

    if (key >= (int)n)
        return 0;
    if (n == 1)
        return (int)(p + *(unsigned short *)(p + 0xC));
    return 0;
}
