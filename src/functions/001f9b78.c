// FUNCTION: SLPM 0x001F9B78
int FUN_001f9b78(char *p, int a1)
{
    int n = *(int *)p;

    if (n == 0)
        return 0;
    for (;;) {
        int v;

        if (*(int *)(p + 4) != 0) {
            v = *(int *)(p + 8);
            if (v != 0 && (unsigned int)(a1 - v) < *(unsigned int *)(p + 0xC))
                return (int)p;
        }
        p = (char *)(p + n) + 4;
        n = *(int *)p;
        if (n == 0)
            return 0;
    }
}
