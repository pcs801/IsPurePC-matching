// FUNCTION: SLPM 001fcb10  size 80  core 76
// ROM keeps p in $a0 and the loop pointer in $a1 and returns p; closest form is void body
// (76/76 with ee29, 15 words off).
extern char D_0026E701[];

void FUN_001fcb10(char *p)
{
    char *q = p;

    while (*q) {
        signed char c = *q;

        if (D_0026E701[c] & 1)
            *q = c + 0x20;
        q++;
    }
}
