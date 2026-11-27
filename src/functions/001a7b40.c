// FUNCTION: SLPM 0x001A7B40  size 72 (core 68)
// OR-accumulate cnt = (n + 3) / 4 ints. Status: 68/68 bytes, 12 words off (scheduling).
int FUN_001a7b40(int *p, int n)
{
    int cnt = (n + 3) / 4;
    int s = 0;

    if (cnt > 0) {
        do {
            s |= *p++;
        } while (--cnt != 0);
    }
    return s;
}
