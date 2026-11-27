extern int D_1BA0D50[];
extern void FUN_0019ed10(void *p, int a);

typedef struct {
    int sx;
    int sy;
    int sw;
    int sh;
} R4;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Rect;

void FUN_0010a2a8(R4 *p, int a1)
{
    Rect r;
    R4 s;

    s = *p;
    s.sx = s.sx + ((D_1BA0D50[4] - 0x6C00) >> 4);
    if ((r.x = s.sx) < 0)
        r.x = 0;
    s.sy = s.sy + ((D_1BA0D50[5] - 0x7200) >> 4);
    if ((r.y = s.sy) < 0)
        r.y = 0;
    if (r.x + s.sw < 640) {
        r.w = s.sw;
    } else {
        r.w = (s.sw - (r.x + s.sw)) + 640;
        if (r.w <= 0)
            return;
    }
    if (r.y + s.sh < 448) {
        r.h = s.sh;
    } else {
        r.h = (s.sh - (r.y + s.sh)) + 448;
        if (r.h <= 0)
            return;
    }
    FUN_0019ed10(&r, (unsigned short)a1);
}
