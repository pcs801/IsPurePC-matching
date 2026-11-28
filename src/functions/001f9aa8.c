int FUN_001f9aa8(char *p)
{
    int c = 0;

    while (*(int *)p != 0) {
        if (*(int *)(p + 4) != 0 && *(int *)(p + 8) != 0)
            c++;
        p = (char *)(p + *(int *)p) + 4;
    }
    return c;
}
