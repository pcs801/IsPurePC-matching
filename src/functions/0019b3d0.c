extern char D_00860D80[];

void FUN_0019b3d0(void)
{
    int i;
    char *p;

    i = 0;
    p = D_00860D80 + 8;
    do {
        i++;
        *(int *)p = 0;
        p += 0x58;
    } while (i < 4);
}
