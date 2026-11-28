extern int FUN_001cf2a8(int a0, int a1, int *a2, int a3, int *a4, int *a5);

int FUN_001b8008(int a0)
{
    int a, b, c;

    FUN_001cf2a8(a0, 2048, &c, 0x00863088, &b, &a);
    return c != 0 ? 0x00863088 : 0;
}
