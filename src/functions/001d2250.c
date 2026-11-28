extern int D_00865E80;
extern char *D_00865E7C;

int FUN_001d2250(void)
{
    char *p = D_00865E7C;
    int i = 0;

    if (D_00865E80 <= 0)
        return 0;
    while (i < D_00865E80) {
        if (*p == 0)
            break;
        i++;
        p += 16;
    }
    return i;
}
