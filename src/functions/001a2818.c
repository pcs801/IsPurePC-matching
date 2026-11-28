extern void FUN_001a1908(int a0, int *a1);

void FUN_001a2818(int a0, int *v, int c, int d, int e)
{
    int buf[4];

    buf[0] = v[0] << 4;
    buf[1] = v[1] << 4;
    buf[2] = (d & 0xFF) << 4;
    buf[3] = (e & 0xFF) << 4;
    FUN_001a1908(a0, buf);
}
