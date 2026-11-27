// FUNCTION: SLPM 0x001A7AF8  size 72 (core 68)
// Sum cnt = (n + 3) / 4 ints (signed-div-by-4 rounding idiom in the target).
// Status: 68/68 bytes, 12 words off - pure scheduling of the pointer copy / division setup.
int FUN_001a7af8(int *p, int n)
{
    int cnt = (n + 3) / 4;
    int s = 0;

    if (cnt > 0) {
        do {
            s += *p++;
        } while (--cnt != 0);
    }
    return s;
}
