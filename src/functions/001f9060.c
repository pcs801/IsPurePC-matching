extern int FUN_001fa8c0(int *p);

void FUN_001f9060(int a0, int a1, int a2, int a3)
{
    int buf[8];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    *(long long *)(buf + 4) = (long long)a3;
    FUN_001fa8c0(buf);
}
