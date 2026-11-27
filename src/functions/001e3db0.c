// FUNCTION: SLPM 0x001E3DB0
int FUN_001e3db0(char *p)
{
    int *a1 = *(int **)p;
    int *a2 = *(int **)(p + 8);

    if (((int)a1 & 0xC) != 0) {
        do {
            *a1 = 0;
            a1++;
        } while (((int)a1 & 0xC) != 0);
    }
    if (a2 != 0)
        *a2 += (((int)a1 - (int)a2) >> 4) - 1;
    *(int **)(p + 8) = 0;
    return (int)a1;
}
