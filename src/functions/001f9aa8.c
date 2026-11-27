// FUNCTION: SLPM 0x001F9AA8
int FUN_001f9aa8(char *p)
{
    int n = *(int *)p;
    int c = 0;

    while (n != 0) {
        if (*(int *)(p + 4) != 0 && *(int *)(p + 8) != 0)
            c++;
        p = (char *)(p + n) + 4;
        n = *(int *)p;
    }
    return c;
}
