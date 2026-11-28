extern void FUN_001f7260(int a0);

void FUN_001f73c0(int a0)
{
    unsigned char *p;

    p = (unsigned char *)a0;
    p[3] = p[3] + 1;
    if (p[3] == 24) {
        p[3] = 0;
        return FUN_001f7260(a0);
    }
}
