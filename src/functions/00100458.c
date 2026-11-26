// FUNCTION: SLPM 0x00100458  (state machine: stream open/step/close, 636 core bytes)
// best-effort reconstruction; MISS: ee-gcc 2.96 keeps the -1 sentinel rematerialised
// instead of hoisting it into $s4, so the prologue saves/restores 5 regs instead of 6
// and every offset after word 8 shifts.

extern int FUN_001fc2a8(char *, char *, int, char *);
extern int FUN_001ad9c8(char *, int);
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
extern char D_0026FC50[];

struct P {
    int f0;
    signed char f4;
    signed char f5;
    char f6;
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

int FUN_00100458(struct S *self)
{
    char buf[0x100];
    struct P *p = self->p;
    int prev = 0;
    int n = p->f0;
    int r;

    if (p->f4 == 1) {
        prev = self->phase;
        self->phase = 100;
    }
    switch (self->phase) {
    case 0:
        if (D_1B74230[0] != 0)
            return 0;
        D_1B74230[0] = 1;
        FUN_001fc2a8(buf, D_0026FC50, n + 8, (char *)p + 6);
        p->f158 = FUN_001ad9c8(buf, 0);
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
        int chunk = 0x800;
        while ((r = FUN_0019c6f8(st[0], chunk)) != -1) {
            st[0] = st[0] + (chunk - r);
            if (!(*(unsigned int *)0x10000000 < (unsigned int)D_00270C18))
                return 0;
        }
        p->f168 = st[2];
        D_1B74230[1] = 0;
        return 1;
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
