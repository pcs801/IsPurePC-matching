extern int FUN_0019f570(int *a0);

int FUN_001a09a0(int a0)
{
    int *p;
    int buf[4];

    p = (int *)a0;
    buf[0] = p[0] << 4;
    buf[1] = p[1] << 4;
    buf[2] = p[2] << 4;
    buf[3] = p[3] << 4;
    return FUN_0019f570(buf);
}
