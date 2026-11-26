// FUNCTION: SLPM 0x001042B0  size 920
extern char D_B1EC00[];
extern char D_A94700[];

extern int FUN_00104648(short);
extern void FUN_00104728(unsigned short, int);
extern void FUN_00105238(int, int);
extern void FUN_00105060(unsigned short, int);
extern void FUN_001053c0(unsigned short, int);
extern void FUN_00105698(int, int);
extern void FUN_00105760(int, int);

typedef struct { int a; int b; unsigned short k; unsigned char pad[2]; } Ent12;
typedef struct { int a; int b; unsigned short k[10]; int pad; } Blk20;
typedef struct { Blk20 *p; int x; } Ent8;
typedef struct { unsigned short k; unsigned short a; int b; int c; int d; } Ent16;

void FUN_001042b0(void) {
    unsigned i, k;
    int j, m, n, ii;
    if (FUN_00104648(0x8010)) {
        char *b = D_B1EC00;
        Ent12 *e = *(Ent12 **)(b + 0x7C);
        for (i = 0; i < *(unsigned *)(b + 0x80); i++)
            FUN_00104728(e[i].k, 1);
    }
    if (FUN_00104648(0x8011)) {
        char *b = D_B1EC00;
        for (i = 0; i < *(unsigned *)(b + 0x20); i++)
            FUN_00105238(i, 1);
    }
    if (FUN_00104648(0x8012)) {
        char *b = D_B1EC00;
        Ent8 *arr = *(Ent8 **)(b + 0x68AC);
        for (k = 0; k < *(unsigned *)(b + 0x68B4); k++) {
            Blk20 *e = arr[k].p;
            for (ii = 0; ii < 3; ii++) {
                for (j = 0; j < 4; j++, e++) {
                    unsigned short *q = e->k;
                    for (m = 9; m >= 0; m--) {
                        if (*q) FUN_00105060(*q, 1);
                        q++;
                    }
                }
            }
        }
    }
    if (FUN_00104648(0x8012)) {
        char *b = D_B1EC00;
        Ent8 *arr = *(Ent8 **)(b + 0x68B8);
        for (k = 0; k < *(unsigned *)(b + 0x68C0); k++) {
            Blk20 *e = arr[k].p;
            for (ii = 0; ii < 3; ii++) {
                for (j = 0; j < 4; j++, e++) {
                    unsigned short *q = e->k;
                    for (m = 9; m >= 0; m--) {
                        if (*q) FUN_00105060(*q, 1);
                        q++;
                    }
                }
            }
        }
    }
    if (FUN_00104648(0x8013)) {
        char *b = D_B1EC00;
        Ent16 *e = *(Ent16 **)(b + 0x68C4);
        for (i = 0; i < *(unsigned *)(b + 0x68C8); i++)
            FUN_001053c0(e[i].k, 1);
    }
    if (FUN_00104648(0x8017)) {
        char *b = D_B1EC00;
        for (i = 0; i < *(unsigned *)(b + 0x6958); i++) {
            FUN_00105698(i, 1);
            FUN_00105760(i, 1);
        }
    }
    if (FUN_00104648(0x8014)) {
        char *b = D_A94700;
        char *p = b + 0x204F;
        for (n = 0x1FFF; n >= 0; n--) *p-- = -1;
        p = b + 0x224F;
        for (n = 0xFF; n >= 0; n--) *p-- = -1;
    }
    if (FUN_00104648(0x8015)) {
        char *b = D_A94700;
        char *p = b + 0x214F;
        for (n = 0xFF; n >= 0; n--) *p-- = -1;
        p = b + 0x22CF;
        for (n = 0x7F; n >= 0; n--) *p-- = -1;
    }
}
