extern void FUN_001a09a0(void *r, void *b, int a2, int a3);

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Rect;

typedef struct {
    signed char a;
    signed char b;
    signed char c;
    signed char d;
} B4;

void FUN_0010a5e8(int a2)
{
    Rect r;
    B4 b;

    r.x = 0;
    r.y = 0;
    r.w = 640;
    r.h = 448;
    b.a = 0;
    b.b = 0;
    b.c = 0;
    b.d = -128;
    FUN_001a09a0(&r, &b, a2, 448);
}
