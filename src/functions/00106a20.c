// FUNCTION: SLPM 0x00106A20
extern void FUN_00205c20(int op);
extern unsigned int FUN_00208690(void *desc, int n);
extern int FUN_00205d40(unsigned int handle);
extern int FUN_0010bd80(unsigned int cmd, void *arg);
extern int FUN_00101bf0(int a0, int a1, unsigned char *a2);
extern int FUN_00101a00(unsigned int a0);
extern void FUN_00107910(void);
extern void FUN_00106268(void);
extern int FUN_00107990(int code);
extern unsigned int D_00270A18;
extern unsigned int D_00270A84;
extern unsigned int D_00270A88;
extern unsigned int D_00270A94;
extern unsigned int D_00270A98;
extern unsigned int D_00270A9C;
extern unsigned char D_00281502;
extern unsigned int D_456500[8];
extern unsigned int D_456490[16];

struct DmaDesc {
    void *ptr;
    unsigned int arg1;
    unsigned int size;
    unsigned int pad;
};

struct Blk {
    unsigned int f0;
    unsigned int f4;
    unsigned int f8;
    unsigned int fC;
};

struct Work {
    unsigned int f0;
    unsigned int f4;
    unsigned int f8;
    unsigned int fC;
    unsigned int dma;
    struct Blk *base;
};

struct Obj {
    unsigned char pad0C[0xC];
    signed char f0C;
    unsigned char f0D;
    unsigned short f0E;
    unsigned short state;
    unsigned char pad12[0x32];
    struct Work *work;
};

int FUN_00106a20(struct Obj *p)
{
    struct Work *w = p->work;
    struct Blk *base = w->base;
    struct DmaDesc d[2];
    unsigned int h;
    unsigned int src;

    switch (p->state) {
    case 0:
        p->f0C = -1;
        if (w->f0 != 0)
            break;
        w->fC = FUN_00101bf0(4, w->f4, (unsigned char *)base + 0xF0000);
        p->state = 1;
    case 1:
        if (FUN_00101a00(w->fC) != 1)
            return 0;
        break;
    case 2:
        d[0].ptr = (void *)((unsigned int)base + (base->f4 << 4) + 0x10);
        d[0].arg1 = D_00270A84;
        d[0].size = 0xE000;
        d[0].pad = 0;
        d[1].ptr = (void *)((unsigned int)base + (base->f8 << 4) + 0x10);
        d[1].arg1 = D_00270A88;
        d[1].size = 0x2000;
        d[1].pad = 0;
        FUN_00205c20(0);
        h = FUN_00208690(d, 2);
        w->dma = h;
        if (h == 0) {
            p->state = 2;
            return 0;
        }
        p->state = 3;
    case 3:
        if (FUN_00205d40(w->dma) >= 0) {
            if (D_00270A18 < *(unsigned int *)0x10000000) {
                p->f0D = 0;
                p->f0E = 0;
            } else {
                p->f0D = 1;
            }
            return 0;
        }
        src = (unsigned int)base + (base->fC << 4) + 0x10;
        D_456500[2] = 0x1000;
        D_00270A98 = src;
        D_00270A9C = 0xC0000;
        D_456500[1] = D_00270A94;
        D_456500[3] = 0xD6000;
        p->state = 4;
    case 4:
        d[0].ptr = (void *)D_00270A98;
        d[0].arg1 = D_00270A94;
        d[0].size = 0x1000;
        d[0].pad = 0;
        FUN_00205c20(0);
        h = FUN_00208690(d, 1);
        w->dma = h;
        if (h == 0) {
            p->state = 2;
            return 0;
        }
        p->state = 5;
    case 5:
        if (FUN_00205d40(w->dma) >= 0) {
            if (D_00270A18 < *(unsigned int *)0x10000000) {
                p->f0D = 0;
                p->f0E = 0;
            } else {
                p->f0D = 1;
            }
            return 0;
        }
        FUN_00205c20(0);
        while (FUN_0010bd80(0x90E0, D_456500) < 0) {
            D_456490[11]++;
            while (FUN_0010bd80(0x80F0, D_456500) != 1)
                ;
        }
        p->state = 6;
    case 6:
        if (FUN_0010bd80(0x80F0, D_456500) != 1) {
            if (D_00270A18 < *(unsigned int *)0x10000000) {
                p->f0D = 0;
                p->f0E = 0;
            } else {
                p->f0D = 1;
            }
            return 0;
        }
        D_456500[3] = D_456500[3] + 0x1000;
        src = D_00270A98 + 0x1000;
        D_00270A98 = src;
        D_00270A9C = D_00270A9C - 0x1000;
        if (D_00270A9C > 0) {
            p->state = 4;
            if (D_00270A18 < *(unsigned int *)0x10000000) {
                p->f0D = 0;
                p->f0E = 0;
            } else {
                p->f0D = 1;
            }
            return 0;
        }
        p->state = 7;
    case 7:
        D_456500[2] = 0xC0000;
        D_456500[0] = D_00270A88;
        D_456500[1] = D_00270A94;
        D_456500[3] = 0xD6000;
        FUN_00205c20(0);
        FUN_0010bd80(0x90B1, D_456500);
        FUN_0010bd80(0xC1, (void *)0x3010);
        FUN_0010bd80(0xD1, (void *)0x100);
        FUN_0010bd80(0x80A0, (void *)D_00270A84);
        if (w->f0 == 0) {
            FUN_00107910();
            D_00281502 = 1;
            FUN_00106268();
            D_456490[8] = FUN_0010bd80(0x8040, (void *)0);
            D_456490[9] = FUN_0010bd80(0x8030, (void *)0);
            D_456490[10] = FUN_0010bd80(0x8010, (void *)0);
            FUN_00107990(-1);
        }
        w->f4 = -1;
        return 1;
    }
    if (D_00281502 != 0) {
        FUN_0010bd80(0xD1, (void *)0);
        D_456490[12] = FUN_0010bd80(0x8020, (void *)0);
        D_456490[13] = FUN_0010bd80(0x8161, (void *)0);
    }
    D_00281502 = 0;
    p->state = 2;
    return 0;
}
