// FUNCTION: SLPM 0x00102A78  size 144 (core 140)
// note: the address is built as (int)pointer + (0x46B0 + i/8) with the integer sum
// formed first; writing p[0x46B0 + i/8] makes ee-gcc emit the pointer add before the
// constant add, which costs 2 differing words.
extern char D_A94700[];
extern int FUN_001fbb84(void *p, int c, int n);

void FUN_00102a78(void)
{
    char *p;
    int i;
    int k;

    D_A94700[0x46B8] = 0;
    FUN_001fbb84(D_A94700 + 0x46CC, 0, 0xC030);
    p = D_A94700 + 9;
    for (i = 0; i < 0x80; i++) {
        k = 0x46B0 + i / 8;
        *(char *)(k + (int)p) &= ~(1 << (i % 8));
    }
}
