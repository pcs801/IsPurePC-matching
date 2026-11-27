// FUNCTION: SLPM 0x001F7140  size 48 (core 44)
// return ((x & 0xFF) / 10 * 6 + (x & 0xFF)) & 0xFF;   (48/44, 11 words rest on register naming)
int FUN_001f7140(unsigned int a0)
{
    unsigned int t = a0 & 0xFF;

    return (t / 10 * 6 + t) & 0xFF;
}
