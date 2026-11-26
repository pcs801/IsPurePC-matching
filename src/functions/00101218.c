// FUNCTION: SLPM 0x00101218  size 592  core 592
struct P {
    int f0;
    signed char f4;
    signed char f5;
    char f6;
    unsigned char pad[0x101];
    int f108;
    int f10C;
    unsigned char pad2[0x9];
    unsigned char f119;
    unsigned char pad3[0x2];
    short f11C;
    short f11E;
    unsigned char pad4[0x30];
    int f150;
    unsigned char pad5[0x8];
    int f15C;
    int f160;
    int f164;
    int f168;
};
extern struct P D_1B75484[10];
extern int D_1B74238;
extern int D_1B7423C[];
extern int FUN_00102020(int);
extern int FUN_00100458(void);
extern int FUN_001006d8(void);
extern int FUN_00100940(void);

extern int FUN_001fc8c0(void *);

int FUN_00101218(int a0, int a1, int a2)
{
    int slot = -1;
    int i;
    int *ref;

    for (i = 0; i < 10; i++) {
        struct P *p = D_1B75484 + i;
        if (p->f10C == 0 && p->f119 == 0) {
            D_1B74238 = i;
            slot = i;
            break;
        }
    }

    ref = (int *)((char *)D_1B7423C + a0 * 0x208);
    {
        struct P *p = D_1B75484 + slot;
        FUN_001fc8c0(&p->f6);
        p->f0 = (int)ref;
        p->f5 = 0;
        p->f119 = 1;
        p->f4 = 0;
        p->f160 = a2;
        p->f15C = a2;
        p->f11C = 0;
        p->f150 = (int)p;
        p->f10C = (int)((char *)FUN_00102020 + 0x18);
        p->f11E = 0;
        switch (*ref) {
        case 0:
            break;
        case 1:
            p->f10C = (int)FUN_00100458;
            break;
        case 2:
            p->f10C = (int)FUN_001006d8;
            break;
        case 3:
            p->f10C = (int)FUN_00100940;
            break;
        }
    }
    for (;;) {
        int lo;
        int hi;
        int j;
        int k;
        int active = 0;

        if (slot == -1) {
            lo = 0;
            hi = 10;
        } else {
            lo = slot;
            hi = slot + 1;
        }
        for (j = lo; j < hi; j++) {
            struct P *q = D_1B75484 + j;
            if (q->f10C != 0) {
                if (q->f11E != 0)
                    q->f119 = 0;
                else
                    active++;
            } else if (q->f11E != 0) {
                q->f119 = 0;
            }
        }
        if (active == 0)
            break;
        for (k = 0; k < 10; k++) {
            struct P *q = D_1B75484 + k;
            int (*cb)(void *) = (int (*)(void *))q->f10C;
            if (cb != 0) {
                int r = cb(&q->f10C);
                if ((unsigned short)r != 0) {
                    q->f11E = (short)r;
                    q->f10C = 0;
                }
            }
        }
    }
    return slot;
}
