extern int D_00270AA8;
extern int D_456540[];
extern int D_4568C0[];
extern int D_456AC0[];
extern unsigned char D_456740[];
extern unsigned char D_4567C0[];
extern unsigned char D_456840[];
extern void FUN_001a09a0(void *p, unsigned char *c, int m);

struct Rect { int x; int y; int w; int h; };

void FUN_001081f8(void)
{
    struct Rect r;
    unsigned char col[4];
    int i;
    int j;
    int prev = 0;
    int diff;
    int sub;
    int over;
    int idx;
    int blk = 0;
    int t;

    if (D_00270AA8 <= 0)
        return;
    for (i = 0; i < D_00270AA8; i++) {
        diff = D_456540[i];
        D_456AC0[i] = i;
        D_4568C0[i] = diff - prev;
        prev = diff;
    }
    for (i = 0; i < D_00270AA8; i++) {
        for (j = i; j < D_00270AA8; j++) {
            if (D_4568C0[j] < D_4568C0[i]) {
                t = D_4568C0[i];
                D_4568C0[i] = D_4568C0[j];
                D_4568C0[j] = t;
                t = D_456AC0[i];
                D_456AC0[i] = D_456AC0[j];
                D_456AC0[j] = t;
            }
        }
    }
    for (i = 0; i < D_00270AA8; i++) {
        diff = D_4568C0[i];
        idx = D_456AC0[i];
        for (;;) {
            if ((blk + 1) * 256 <= diff) { sub = 256; over = 1; }
            else { sub = diff % 256; over = 0; }
            r.x = 0x278 - blk * 8;
            r.y = 0;
            r.w = 8;
            r.h = sub * 2;
            col[0] = D_456740[idx];
            col[1] = D_4567C0[idx];
            col[2] = D_456840[idx];
            col[3] = 0x80;
            FUN_001a09a0(&r, col, 0x1F);
            blk++;
            if (!over) break;
        }
    }
}
