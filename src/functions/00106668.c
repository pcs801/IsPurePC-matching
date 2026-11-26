// FUNCTION: SLPM 0x00106668  size 336 (core 332)
extern unsigned char D_270E80[];
extern int D_00270C3C;
extern int D_00270AA0;
extern unsigned int D_873F00[];
extern void FUN_00107728(short a0);
extern void FUN_001b6fa0(int a0);
extern void FUN_001b9e58(int a0, void *a1);

void FUN_00106668(short sel)
{
    unsigned char *p;
    int *blk;
    unsigned int *t;
    unsigned int off;

    FUN_00107728(sel);
    p = D_270E80;
    p[sel + 2] = 1;
    blk = (int *)(p + (*(int *)(p + 0x18) * 0x4180 + 0x80));
    if (blk[0] + 6 < D_00270C3C) {
        FUN_001b6fa0(blk[1]);
        off = ((D_873F00[0] * 4 + 0x13) >> 4) + D_873F00[1];
        t = (unsigned int *)((char *)D_873F00 + (off << 4));
        off = ((t[0] * 4 + 0x13) >> 4) + (&t[1])[sel];
        FUN_001b9e58(*(int *)(p + *(int *)(p + 0x18) * 0x4180 + 0x84),
                     (char *)t + (off << 4));
        *(int *)(p + *(int *)(p + 0x18) * 0x4180 + 0x80) = D_00270C3C;
        *(int *)(p + 0x18) = (*(int *)(p + 0x18) + 1) % 4;
    }
    D_00270AA0 = sel;
}
