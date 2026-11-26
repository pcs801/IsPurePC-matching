// FUNCTION: SLPM 0x00100940  size 688  core 688
// sig: addiu ; sd ; addiu ; sd ; daddu ; sd ; daddu ; sd ; sd ; sd ; sd ; sd
// stream state machine (phase 0/1/2/3/100), sibling of 0x00100458 / 0x001006D8.

extern int FUN_001fc2a8(char *, char *, int, char *);
extern int FUN_0010b290(char *, int, char *);
extern int FUN_0010b6a8(char *);
extern int FUN_001fbad4(int, int, int);
extern int FUN_0010baa8(char *);
extern int FUN_0010bb18(char *);
extern int FUN_0019c928(int, int);
extern int FUN_0019c6f8(int, int);
extern int D_1B74230[];
extern int D_1B9F908[];
extern int D_1B76300[];
extern int D_00270C18;
extern char D_0026FC50[];

struct P {
    int f0;
    signed char f4;
    signed char f5;
    char f6;
    unsigned char pad[0x155];
    int f15C;
    int f160;
    int f164;
    int f168;
};

struct S {
    unsigned char pad[0x10];
    short phase;
    unsigned char pad2[0x32];
    struct P *p;
};

int FUN_00100940(struct S *self)
{
    char buf[0x100];
    struct P *p = self->p;
    int prev = 0;
    int n = p->f0;

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
        FUN_0010b290((char *)D_1B76300, n + 0x108, buf);
        p->f164 = p->f160;
        self->phase = 1;
    case 1:
        do {
            prev = FUN_0010b6a8((char *)D_1B76300);
            FUN_001fbad4(p->f164, D_1B76300[0x7EB4 / 4],
                         D_1B76300[0x7EB8 / 4]);
            p->f164 += D_1B76300[0x7EB8 / 4];
            if (prev == 1) {
                FUN_0010baa8((char *)D_1B76300);
                p->f168 = p->f164 - p->f160;
                D_1B74230[0] = 0;
                if (p->f5 == 0)
                    return 1;
                self->phase = 2;
                return 0;
            }
        } while (*(unsigned int *)0x10000000 < (unsigned int)D_00270C18);
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
        while ((prev = FUN_0019c6f8(st[0], chunk)) != -1) {
            st[0] = st[0] + (chunk - prev);
            if (!(*(unsigned int *)0x10000000 < (unsigned int)D_00270C18))
                return 0;
        }
        p->f168 = st[2];
        D_1B74230[1] = 0;
        return 1;
    }
    case 100:
        if (prev == 1) {
            FUN_0010bb18((char *)D_1B76300);
            FUN_0010baa8((char *)D_1B76300);
        }
        D_1B74230[1] = 0;
        D_1B74230[0] = 0;
        p->f4 = 0;
        return 1;
    }
    return 0;
}
