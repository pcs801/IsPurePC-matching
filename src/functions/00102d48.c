// FUNCTION: SLPM 0x00102D48  size 1744 (core 1740) — region holds two functions:
//   [A] 0x102D48..0x102FB0 (616 B) compaction helper with start argument  (this file)
//   [B] 0x102FB8..0x103414 (1116 B) GS state block, two 5-entry tables (separate task)
extern char D_A94700[];
extern char D_A98DCC[];
extern int FUN_001fbb84(void *p, int c, int n);

struct Blk { int w[0x7B]; };

void FUN_00102d48(int start)
{
    int i = start;
    int n = start;
    int k;

    if (i < 100) {
        char *base = D_A94700;
        unsigned char *bits = base + 9;
        char *src = base + 0x46CC + i * 0x1EC;
        char *dst = src;

        for (; i < 100; i++, src += 0x1EC) {
            if ((*(unsigned char *)((int)(i / 8) + (int)bits + 0x46B0) >> (i % 8)) & 1) {
                *(struct Blk *)dst = *(struct Blk *)src;
                dst += 0x1EC;
                k = 0x46B0 + n / 8;
                *(char *)(k + (int)bits) |= 1 << (n % 8);
                n++;
            }
        }
    }
    i = n;
    if (i < 100) {
        char *p = (char *)D_A98DCC + n * 0x1EC;
        unsigned char *b = (unsigned char *)D_A98DCC - 0x46C3;
        for (; i < 100; i++) {
            FUN_001fbb84(p, 0, 0x1EC);
            p += 0x1EC;
            {
                int q = (int)(i / 8) + 0x46B0;
                *(b + q) &= ~(1 << (i % 8));
            }
        }
    }
    D_A94700[0x46B8] = n;
}
