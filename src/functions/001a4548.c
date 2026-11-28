extern int FUN_001a2fd0(int a0, int *b);

int FUN_001a4548(int a0, int *p)
{
    int buf[6];

    buf[0] = p[0] << 4;
    buf[1] = p[1] << 4;
    buf[2] = p[2] << 4;
    buf[3] = p[3] << 4;
    buf[4] = p[4] << 4;
    buf[5] = p[5] << 4;
    return FUN_001a2fd0(a0, buf);
}
