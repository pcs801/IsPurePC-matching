extern void FUN_001a1908(int a0, int *a1);

void FUN_001a2860(int a0, int *v)
{
    int b0, b1, b2, b3;
    int buf[4];

    b3 = v[3] << 4;
    b0 = v[0] << 4;
    b1 = v[1] << 4;
    b2 = v[2] << 4;
    buf[0] = b0;
    buf[1] = b1;
    buf[2] = b2;
    buf[3] = b3;
    FUN_001a1908(a0, buf);
}
