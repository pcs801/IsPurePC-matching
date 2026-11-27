// FUNCTION: SLPM 0x00102B08  size 576 (core 572)
// MISS: 580/572 bytes, words 0..97 identical; the remaining gap is the tail section
// (count-slot rematerialisation scheduled early + one loop-alignment nop + the tail
// bit-clear register split). Structure recovered:
//   * 100 slots of 0x1EC bytes at D_A94700+0x46CC; a 0x80-bit map lives at
//     D_A94700+0x46B9 (accessed as bits+0x46B0 with bits = base+9).
//   * compaction loop: if bit i set, copy slot i to the dst cursor (struct assignment
//     of a 4-byte-aligned 0x1EC-byte block => ldl/ldr/sdl/sdr + lw tail), set bit n.
//   * tail: if n < 100, memset the remaining slots and clear their bits, then publish
//     the count at D_A94700+0x46B8.
extern char D_A94700[];
extern char D_A98DCC[];
extern int FUN_001fbb84(void *p, int c, int n);

struct Blk { int w[0x7B]; };

void FUN_00102b08(void)
{
    char *base = D_A94700;
    unsigned char *bits = base + 9;
    char *src = base + 0x46CC;
    char *dst = base + 0x46CC;
    int i;
    int n = 0;
    int k;

    for (i = 0; i < 0x64; i++, src += 0x1EC) {
        if ((*(unsigned char *)((int)(i / 8) + (int)bits + 0x46B0) >> (i % 8)) & 1) {
            *(struct Blk *)dst = *(struct Blk *)src;
            dst += 0x1EC;
            k = 0x46B0 + n / 8;
            *(char *)(k + (int)bits) |= 1 << (n % 8);
            n++;
        }
    }
    if (n < 0x64) {
        char *p = (char *)D_A98DCC + n * 0x1EC;
        unsigned char *b = (unsigned char *)D_A98DCC - 0x46C3;
        for (i = n; i < 0x64; i++) {
            FUN_001fbb84(p, 0, 0x1EC);
            p += 0x1EC;
            k = 0x46B0 + i / 8;
            *(char *)(k + (int)b) &= ~(1 << (i % 8));
        }
    }
    D_A94700[0x46B8] = n;
}
