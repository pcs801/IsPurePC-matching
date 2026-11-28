int FUN_002034f0(int a0, int *a1, unsigned char *a2, int a3)
{
    int r = 0;
    int local;
    int *dst = a1 != 0 ? a1 : &local;

    if (a2 == 0)
        r = 0;
    else if (a3 == 0)
        r = -1;
    else {
        *dst = *a2;
        r = *a2 != 0;
    }
    return r;
}
