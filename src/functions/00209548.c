extern int FUN_00208c78(int a0, char *p, int a2, int a3, int a4, int a5);

int FUN_00209548(int a0, int a1, int a2, char *p)
{
    int r = 2048;

    if (FUN_00208c78(0x80000008, p, 64, 0, 0, 0) != 0)
        r = 0;
    return r;
}
