// FUNCTION: SLPM 001fe618  size 80  core 76
// ROM keeps p in $a0 and the loop pointer in $a1 and returns p; closest form is void body
// (76/76 with ee29, 15 words off).
extern char D_0026E701[];

void FUN_001fe618(char *p)
{
    char *q = p;

    while (*q) {
        signed char c = *q;

        if (D_0026E701[c] & 2)
            *q = c - 0x20;
        q++;
    }
}
