extern int FUN_001a12a8(int a0, int *a1);

int FUN_001a27e0(int a0, int *a1)
{
    int buf[4];
    int x;
    int y;

    x = a1[1] << 4;
    y = a1[0] << 4;
    buf[1] = x;
    buf[0] = y;
    return FUN_001a12a8(a0, buf);
}
