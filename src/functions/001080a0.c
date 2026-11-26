extern int D_00270AA8;
extern int D_456540[];
extern unsigned char D_456740[];
extern unsigned char D_4567C0[];
extern unsigned char D_456840[];
extern void FUN_001a09a0(void *p, unsigned char *c, int m);

struct Rect { int x; int y; int w; int h; };

void FUN_001080a0(void)
{
    struct Rect r;
    unsigned char col[4];
    int i = 0;
    int j = 0;
    int prev = 0;
    int diff;
    int sub;
    int over;

    if (D_00270AA8 <= 0)
        return;
    do {
        diff = D_456540[i] - prev;
        for (;;) {
            if (((j + 1) << 8) <= diff) { sub = 256; over = 1; }
            else { sub = diff % 256; over = 0; }
            r.x = j * 4;
            r.y = 0;
            r.w = 4;
            r.h = sub * 2;
            col[0] = D_456740[i];
            col[1] = D_4567C0[i];
            col[2] = D_456840[i];
            col[3] = 0x80;
            FUN_001a09a0(&r, col, 0x1F);
            j++;
            if (!over) break;
        }
        prev = D_456540[i];
        i++;
    } while (i < D_00270AA8);
}
