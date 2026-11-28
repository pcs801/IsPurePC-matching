extern void FUN_001a1908(int a0, int *a1);

void FUN_001a28b0(int a0, int *v)
{
    int buf[4];

    buf[0] = v[0] << 4;
    buf[1] = v[1] << 4;
    buf[2] = v[2] << 4;
    buf[3] = v[3] << 4;
    FUN_001a1908(a0, buf);
}
