extern int D_1BA0D50[];
extern void FUN_0019ed10(void *p, int a);

typedef struct {
    int v[4];
} R4;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    R4 src;
} Clip;

void FUN_0010a2a8(R4 *src, int a1)
{
    Clip c;

    c.src = *src;

    c.src.v[0] = c.src.v[0] + ((D_1BA0D50[4] - 0x6C00) >> 4);
    c.x = c.src.v[0];
    if (c.x < 0)
        c.x = 0;

    c.src.v[1] = c.src.v[1] + ((D_1BA0D50[5] - 0x7200) >> 4);
    c.y = c.src.v[1];
    if (c.y < 0)
        c.y = 0;

    if (c.x + c.src.v[2] < 640) {
        c.w = c.src.v[2];
    } else {
        c.w = c.src.v[2] - ((c.x + c.src.v[2]) - 640);
        if (c.w <= 0)
            return;
    }

    if (c.y + c.src.v[3] < 448) {
        c.h = c.src.v[3];
    } else {
        c.h = c.src.v[3] - ((c.y + c.src.v[3]) - 448);
        if (c.h <= 0)
            return;
    }

    FUN_0019ed10(&c, (unsigned short)a1);
}
