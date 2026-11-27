void FUN_0019b688(char *p)
{
    int n = *(int *)(p) * *(int *)(p + 4);
    short *q = *(short **)(p + 8);

    while (n-- != 0)
        *q++ = 0x720;
    *(int *)(p + 16) = 0;
    *(int *)(p + 20) = 0;
}