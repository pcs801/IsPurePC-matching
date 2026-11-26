// FUNCTION: SLPM 0x001464A0  size 256  core 252
// best-effort candidate (MISS): GCC 2.96 strength-reduces the inner address,
// target instead recomputes base + n*2 each iteration.
extern void FUN_001050f8(unsigned short v, int f);

void FUN_001464a0(char *p) {
    int i, j, n;
    char *f = p + 0x528;
    char *b = p + 0x548;
    for (i = 0; i < *(int*)(p + 0x404); i++) {
        for (j = 11; j >= 0; j--) {
            if (*f != 0) {
                unsigned short *sp = (unsigned short*)(b + 8);
                char *cp = b + 0x24;
                for (n = 0; n < 32; n++) {
                    int m = n + n;
                    if (sp[n] == 0) break;
                    if (*cp != 0) FUN_001050f8(sp[m], 1);
                    cp++;
                }
            }
            b += 0x44;
        }
        f++;
    }
}
