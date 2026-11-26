// FUNCTION: SLPM 0x00100BF0  size 400  core 400
// sig: addiu ; addiu ; sd ; sd ; sd ; sd ; sd ; sd ; sd ; sd ; sd ; bne

struct P {
    int f0;
    signed char f4;
    signed char f5;
    char f6;
    unsigned char pad[0x101];
    int f108;
    int f10C;
    unsigned char pad2[0x9];
    signed char f119;
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

int FUN_00100bf0(int a0)
{
    int i;
    int end;

    if (a0 == -1) {
        a0 = 0;
        end = 10;
    } else {
        end = a0 + 1;
    }
    for (i = a0; i < end; i++) {
        struct P *cur = D_1B75484 + i;
        int lo;
        int hi;
        int j;
        int active = 0;

        if (i == -1) {
            lo = 0;
            hi = 10;
        } else {
            lo = i;
            hi = i + 1;
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
        if (active != 0) {
            int k;
            cur->f4 = 1;
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
    }
    return 0;
}
