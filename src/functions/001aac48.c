extern int FUN_001a9ed0(int a0, int a1, char *a2, int a3, int a4);

int FUN_001aac48(int a0, int *p)
{
    int r;

    if (FUN_001a9ed0(a0, 16, (char *)p, 0, 4) >= 0) {
        r = *p;
        return r;
    }
    return -542;
}
