// FUNCTION: SLPM 0x001A9588  size 552  core 548
extern char D_860EE0[];
extern unsigned char D_0026E701[];
extern void FUN_001fc2a8(char *out, char *fmt, int arg);
extern int FUN_001fc9d4(char *);
typedef char *va_list;

int FUN_001a9588(char *s, ...)
{
    char buf[0x100];
    va_list ap;
    char *base;
    char *out;
    int c;
    int lc;
    int arg;

    __builtin_stdarg_start(&ap, s);
    base = D_860EE0;
    out = base + 0x3C + *(int *)(base + 0x38) * 30;

    for (;;) {
        c = *(signed char *)s;
        if (c == '%') {
            buf[0] = (char)c;
            s++;
            for (;;) {
                lc = *(signed char *)s;
                buf[1] = (char)lc;
                if (D_0026E701[lc] & 1)
                    lc += 0x20;
                if (lc == 'd' || lc == 'i' || lc == 'o' || lc == 'u' ||
                    lc == 'e' || lc == 'g' || lc == 'c' || lc == 's' ||
                    lc == 'x' || lc == 'f') {
                    arg = *(int *)ap;
                    ap += 8;
                    buf[2] = 0;
                    FUN_001fc2a8(out, buf, arg);
                    out += FUN_001fc9d4(out);
                    s++;
                    break;
                }
                if (lc == 0)
                    break;
                if (lc == 0x0A)
                    break;
                *out = (char)lc;
                out++;
                s++;
            }
            continue;
        }
        if (c >= 0x26) {
            *out = (char)c;
            out++;
            s++;
            continue;
        }
        if (c == 0 || c == 0x0A)
            break;
        *out = (char)c;
        out++;
        s++;
    }
    {
        int *p = (int *)(base + 0x38);
        *p = (*p + 1) % 5;
    }
    return 0;
}
