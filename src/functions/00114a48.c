// FUNCTION: SLPM 0x00114A48
extern char D_1B73FC0[];
extern int D_00B1EC00[];
extern int D_00270C38;

void FUN_00114a48(void)
{
    char *p = D_1B73FC0;
    unsigned short v = *(unsigned short *)D_00B1EC00[0];
    short *q;
    char *r;
    char *s;
    int i;

    *(int *)(p + 0xD0) = 0;
    *(int *)(p + 0xD4) = v;
    p[0xE2] = -1;
    p[0xE3] = -0x80;
    *(int *)(p + 0xCC) = v;
    *(int *)(p + 0xD8) = 0;
    *(short *)(p + 0xDC) = 0;
    *(int *)(p + 0xEC) = 0;
    *(int *)(p + 0xF0) = 0;
    p[0xE4] = 0;

    q = (short *)(p + 0x106);
    for (i = 2; i >= 0; i--) {
        q[-1] = -1;
        q[0] = 0x80;
        q += 2;
    }

    r = p + 0x120;
    for (i = 0; i < 6; i++) {
        *(short *)(r - 0x10) = -1;
        *(short *)(r - 0x0E) = 0;
        *(short *)(r - 0x0C) = 0;
        *(short *)(r - 0x0A) = 0;
        *(short *)(r - 0x08) = 0;
        *(short *)(r - 0x06) = 0x280;
        *(short *)(r - 0x04) = 0x1C0;
        *(char *)(r - 0x02) = 0;
        *(char *)(r - 0x01) = i;
        *(char *)(r + 0x00) = 0;
        *(char *)(r + 0x01) = 0;
        r += 0x12;
    }

    *(short *)(p + 0x11C) = 0x1C0;
    *(short *)(p + 0x110) = 0x1000;
    *(short *)(p + 0x11A) = 0x280;

    s = p + 0x1C4;
    for (i = 2; i >= 0; i--) {
        *s = 0;
        s -= 0x24;
    }

    D_00270C38 = 0;
    p[0xE1] = 0;
    *(short *)(p + 0x1E8) = 0;
    *(short *)(p + 0x1EA) = 0;
    p[0xE0] = 0;
}
