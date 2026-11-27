extern int FUN_001c1820(int a0, int *buf);

int FUN_001c1bc8(int a0)
{
    int buf[12];

    FUN_001c1820(a0, buf);
    return buf[0] != 0;
}
