extern int D_00270AA8;
extern unsigned char D_456740[];
extern unsigned char D_4567C0[];
extern unsigned char D_456840[];
extern int D_456540[];
extern void FUN_001a09a0(void *p, unsigned char *c, int m);

void FUN_00107f30(void)
{
    struct Rect { int x; int y; int w; int h; } r;
    unsigned char col[4];
    int i = 0;
    int j = 0;
    int prev = 0;
    int sub;
    int over;

    if (D_00270AA8 <= 0)
        return;
    do {
        do {
            if (D_456540[i] >= (j + 1) * 256) {
                sub = 256;
                over = 1;
            } else {
                sub = D_456540[i] % 256;
                over = 0;
            }
            r.x = j * 8;
            r.y = sub * 2;
            r.w = 8;
            r.h = (prev - sub) * 2;
            col[0] = D_456740[i];
            col[1] = D_4567C0[i];
            col[2] = D_456840[i];
            col[3] = 0x80;
            FUN_001a09a0(&r, col, 0x1F);
            if (!over) { prev = sub; break; }
            prev = 0;
            j++;
        } while (1);
        i++;
    } while (i < D_00270AA8);
}
