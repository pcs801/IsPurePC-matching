// FUNCTION: SLPM 0x00111AD0  size 432  core 428
extern int FUN_001e9090(int, int, int);
extern void FUN_00111f78(int *, int *, int *, int *, void *, int);
extern int FUN_00112020(int, int, int, int, int, int);

int FUN_00111ad0(char *p)
{
    int buf[4];
    int s1 = 0;
    int t4;
    int a1;
    int v0;
    int v1;
    int t1;
    int t0;
    int t3;

    switch (*(int *)p) {
    case 0:
        return 0;
    case 1:
        buf[0] = *(int *)(p + 0x44) + *(int *)(p + 0x54) % *(int *)(p + 0x48);
        buf[1] = *(int *)(p + 0x48) - *(int *)(p + 0x54);
        buf[2] = 0;
        buf[3] = 0;
        break;
    case 2:
        FUN_00111f78(buf, buf + 1, buf + 2, buf + 3, p,
                     (FUN_001e9090(1, 0x8100, 1) & 0xFFFFFF) - *(int *)(p + 0x44));
        break;
    case 3:
        return 0;
    default:
        break;
    }

    t4 = *(int *)(p + 0x38);
    a1 = *(int *)(p + 0x3C);
    v0 = *(int *)(p + 0x34) - t4 + a1;
    v1 = t4 / 1024 * 1024;
    t1 = a1 - v0 % a1;
    t0 = *(int *)(p + 0x30) + v0 % a1;
    if (v1 < t1)
        t1 = v1;
    t3 = v1 - t1;
    if (buf[1] + buf[3] >= 0x400) {
        if (t1 + t3 >= 0x400)
            s1 = FUN_00112020(buf[0], buf[1], buf[2], buf[3], t0, t1);
    }
    *(int *)(p + 0x38) = *(int *)(p + 0x38) - s1;
    *(int *)(p + 0x54) = *(int *)(p + 0x54) + s1;
    *(int *)(p + 0x4C) = (*(int *)(p + 0x4C) + s1) % *(int *)(p + 0x48);
    return s1;
}
