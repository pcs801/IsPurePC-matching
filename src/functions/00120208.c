// FUNCTION: SLPM 0x00120208  size 416  core 416
extern int *D_00270CB0;
extern unsigned char *D_00270CAC;
extern void FUN_00171878(int);

void FUN_00120208(void)
{
    int fp;
    int s4;
    int s5;
    int s6;
    int s2;
    unsigned char *s0;
    unsigned char *s1;
    unsigned char *s7;
    int a1;
    int v1;
    int v0;

    if (D_00270CAC[0x47C] == 1)
        fp = 0x1B8;
    else if (D_00270CB0[5] == 0)
        fp = 2;
    else
        fp = 0x1B8;
    s4 = 0;
    for (;;) {
        v0 = D_00270CB0[0];
        D_00270CB0[0] = s4;
        s5 = 0;
        v0 = ((s4 * 3) << 10) - s4;
        v0 <<= 3;
        s6 = *(int *)((char *)D_00270CB0 + v0 + 0xA4);
        s0 = (unsigned char *)D_00270CB0 + v0 + 0x18;
        s7 = (unsigned char *)D_00270CB0 + v0 + 0x5C3C;
        a1 = *(int *)(s0 + 0x68);
        *(int *)(s0 + 0x8C) = s6;
        v0 = ((a1 * 3) << 2) + a1;
        v0 <<= 2;
        s1 = s0 + v0 + 0x94;
        v1 = *(int *)(D_00270CB0 + 0);
        s2 = (((v1 << 3) - v1) << 3) - v1;
        s2 <<= 3;
        *(int *)(s0 + 0x90) = s2;
        for (;;) {
            int idx;
            if (fp == s5)
                break;
            idx = *(int *)(s0 + 0x64);
            a1 = *(int *)(s0 + 0x68);
            if (idx >= a1)
                break;
            if (*(signed char *)(s7 + idx * 2) != 0)
                FUN_00171878(s2 + idx);
            idx++;
            *(int *)(s0 + 0x64) = idx;
            if (*(int *)s1 > 0)
                break;
            s1 += 0x34;
            s5++;
        }
        s4++;
        if (s4 > 0)
            break;
    }
}
