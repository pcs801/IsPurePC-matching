// FUNCTION: SLPM 0x001006D8 placeholder

extern int FUN_001adef8(int, int);
extern int FUN_001aed00(int);
extern int FUN_001ae6f8(int, int, int);
extern int FUN_001af038(int);
extern int FUN_001ae128(int);
extern int FUN_001ae790(int);
extern int FUN_0019c928(int, int);
extern int FUN_0019c6f8(int, int);
extern int D_1B74230[];
extern int D_1B9F908[];
extern int D_00270C18;

struct P {
    void *f0;
    signed char f4;
    signed char f5;
    unsigned char pad[0x100];
    int f108;
    unsigned char pad2[0x4C];
    int f158;
    int f15C;
    int f160;
    unsigned char pad3[4];
    int f168;
};

struct S {
    unsigned char pad[0x10];
    short phase;
    unsigned char pad2[0x32];
    struct P *p;
};

int FUN_001006d8(struct S *self)
{
    struct P *p = self->p;
    int prev = 0;
    int r;
    int chunk;
    int eof;

    if (p->f4 == 1) {
        prev = self->phase;
        self->phase = 100;
    }
    switch (self->phase) {
    case 0:
        if (D_1B74230[0] != 0)
            return 0;
        D_1B74230[0] = 1;
        p->f158 = FUN_001adef8(*(int *)(*(int *)p->f0 + 4), p->f108);
        p->f168 = FUN_001aed00(p->f158);
        FUN_001ae6f8(p->f158, p->f168, p->f160);
        self->phase = 1;
        p->f168 = p->f168 << 11;
    case 1:
        r = FUN_001af038(p->f158);
        if (r == 3) {
            FUN_001ae128(p->f158);
            D_1B74230[0] = 0;
            if (p->f5 == 0)
                return 1;
            self->phase = 2;
        } else if (r == 4) {
            FUN_001ae128(p->f158);
            D_1B74230[0] = 0;
            self->phase = 0;
        }
        return 0;
    case 2:
        if (D_1B74230[1] != 0)
            return 0;
        D_1B74230[1] = 1;
        if (p->f15C == 0)
            p->f15C = (p->f160 + p->f168 + 0xF) >> 4 << 4;
        FUN_0019c928(p->f160, p->f15C);
        self->phase = 3;
    case 3: {
        int *st = D_1B9F908;
        chunk = 0x800;
        eof = -1;
        while (1) {
            r = FUN_0019c6f8(st[0], 0x800);
            if (r == eof) {
                p->f168 = st[2];
                D_1B74230[1] = 0;
                return 1;
            }
            st[0] = st[0] + (chunk - r);
            if (!(*(unsigned int *)0x10000000 < (unsigned int)D_00270C18))
                break;
        }
        return 0;
    }
    case 100:
        if (prev == 1) {
            FUN_001ae790(p->f158);
            FUN_001ae128(p->f158);
        }
        D_1B74230[1] = 0;
        D_1B74230[0] = 0;
        p->f4 = 0;
        return 1;
    }
    return 0;
}