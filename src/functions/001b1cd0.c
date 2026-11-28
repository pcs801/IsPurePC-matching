extern int FUN_001b11b8(int *a0);

void FUN_001b1cd0(int *p)
{
    int buf[6];

    if (p != 0) {
        buf[0] = p[0];
        buf[1] = p[1];
        buf[2] = p[2];
        buf[3] = p[2] + 1;
        buf[4] = p[3];
        buf[5] = 25;
        FUN_001b11b8(buf);
        return;
    }
    FUN_001b11b8(0);
}
