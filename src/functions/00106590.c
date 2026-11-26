// FUNCTION: SLPM 0x00106590  size 216 (core 212)
extern unsigned char D_270E80[];
extern unsigned int D_456490[];
extern unsigned int D_00270AA0;
extern unsigned int D_00270AA4;
extern unsigned int FUN_001b64c8(int a, unsigned int addr, unsigned int size);
extern void FUN_001fbb84(void *dst, int val, unsigned int n);

void FUN_00106590(void)
{
    unsigned char *p;
    unsigned char *q;
    unsigned int *e;
    unsigned int off;
    int i;

    p = D_270E80;
    q = p + 0x15;
    p[1] = 3;
    p[0] = 0x80;
    for (i = 0x13; i >= 0; i--) {
        *q = 0;
        q--;
    }
    p = D_270E80;
    *(unsigned int *)(p + 0x18) = 0;
    e = (unsigned int *)(p + 0x80);
    off = 0;
    for (i = 3; i >= 0; i--) {
        *e = 0;
        e[1] = FUN_001b64c8(1, off + (unsigned int)(p + 0x100), 0x4100);
        e = (unsigned int *)((char *)e + 0x4180);
        off += 0x4180;
    }
    FUN_001fbb84(D_456490, 0, 0x50);
    D_00270AA4 = -1;
    D_00270AA0 = -1;
}
