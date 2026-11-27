// FUNCTION: SLPM 0x0018A018
int FUN_0018a018(char *a0, char *a1, int a2)
{
    char *p;
    char *q;
    char *r;
    char c;
    int n;

    p = a0;
    n = 0;
    c = *a1;
    if (a2 <= 0)
        return 0;
    while (n < a2) {
        if (*p == c) {
            q = p;
            r = a1;
            for (;;) {
                if ((int)(q - a0) == a2) {
                    n++;
                    break;
                }
                if (*r == 0)
                    return (int)p;
                if (*q != *r) {
                    n++;
                    break;
                }
                q++;
                r++;
            }
        } else {
            n++;
        }
        p++;
    }
    return 0;
}
