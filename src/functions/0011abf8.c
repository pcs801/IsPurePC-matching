// FUNCTION: SLPM 0x0011ABF8  size 1544  core 1544
// sig: addiu ; lw ; sd ; daddu ; sd ; sd ; sd ; sd ; sd ; sd ; lbu ; bnez

extern int *D_00270CAC;
extern unsigned char D_00A98DA3;
extern void FUN_001161c0(void);
extern void FUN_001157f8(int id, int v);
extern int FUN_001058a8(int a, int b);
extern int FUN_001fbe00(void);
extern int FUN_00115730(int a);
extern int FUN_00115d38(int a, int b);
extern int FUN_00127f78(int a0, int a1, int a2, int a3, int a4, int a5);
extern int FUN_00128328(int a);
extern void FUN_00123070(void);
extern void FUN_00122d18(void);
extern void FUN_00117760(void);
extern void FUN_00116ad0(void);
extern void FUN_00117920(void);
extern void FUN_00106668(int a);
extern void FUN_001280d0(int a);
extern int FUN_001282f8(void);
extern void FUN_00115e60(int a, int b);
extern void FUN_00128340(void);
extern void FUN_001283c8(void);
extern void FUN_00117dc0(int *st);

int FUN_0011abf8(int *st)
{
    int *s;
    int *p;
    int base;
    int phase;
    int order[16];

    if (*(unsigned char *)((char *)D_00270CAC + 0x479) != 0) {
        *(unsigned char *)((char *)st + 0xD) = 0;
        *(short *)((char *)st + 0xE) = 0;
        return 0;
    }
    s = (int *)*(int *)((char *)st + 0x44);
    phase = *(short *)((char *)st + 0x10);
    p = (int *)*(int *)((char *)s + 8);
    base = *(int *)((char *)s + 0xC) + *(int *)((char *)p + 4);

    switch (phase) {
    case 0: {
        int *o;
        int i;
        int hit;
        int idx;
        int tmp;
        int v;

        if (*(unsigned char *)((char *)D_00270CAC + 0x4FC) != 0) {
            *(unsigned char *)((char *)D_00270CAC + 0x4FC) = 0;
        } else if (*(unsigned char *)((char *)D_00270CAC + 0x4C5) != 0) {
            *(unsigned char *)((char *)D_00270CAC + 0x4FC) = 0;
        } else {
            FUN_001161c0();
            *(unsigned char *)((char *)D_00270CAC + 0x4FC) = 0;
        }
        FUN_001157f8(*(unsigned short *)((char *)p + 2), -1);
        *(int *)((char *)D_00270CAC + 0x4D8) = 0;
        if (*(unsigned char *)p == 0x72) {
            v = FUN_001058a8(*(int *)((char *)D_00270CAC + 0x52E0),
                             *(unsigned short *)((char *)p + 0xA));
            *(int *)((char *)D_00270CAC + 0x3B7E4) = v;
            *(int *)((char *)D_00270CAC + 0x3B7E0) =
                *(unsigned short *)((char *)p + 0xA) + 1;
        } else {
            *(int *)((char *)D_00270CAC + 0x3B7E0) = 0;
            *(int *)((char *)D_00270CAC + 0x3B7E4) = 0;
        }
        o = order;
        for (i = 0; i < *(unsigned char *)((char *)p + 1); i++)
            *o++ = i;
        hit = 0;
        if (*(unsigned char *)p == 0x71) {
            o = order;
            for (i = 0; i < *(unsigned char *)((char *)p + 1); i++, o++) {
                idx = FUN_001fbe00() % *(unsigned char *)((char *)p + 1);
                tmp = *o;
                *o = order[idx];
                order[idx] = tmp;
            }
        }
        hit = 0;
        o = order;
        for (i = 0; i < *(unsigned char *)((char *)p + 1); i++, o++) {
            if (FUN_00115730(*(short *)(base + *o * 12 + 8)) != 0) {
                hit++;
                v = FUN_00115d38(*(int *)((char *)D_00270CAC + 0x52E0),
                                 *(unsigned short *)(base + *o * 12 + 0xA));
                FUN_00127f78(*o, -1, -1, 1, *(int *)(base + *o * 12 + 4), v);
                s = (int *)*(int *)((char *)st + 0x44);
                FUN_00128328(*(int *)((char *)s + 0xC) + *(int *)(base + *o * 12));
            }
        }
        *(int *)((char *)D_00270CAC + 0x49C) = hit;
        if (hit == 0) {
            FUN_001157f8(*(unsigned short *)((char *)p + 2),
                         *(unsigned char *)((char *)p + 1));
            FUN_00123070();
            FUN_00122d18();
            s = (int *)*(int *)((char *)st + 0x44);
            v = *(int *)((char *)s + 8);
            if (*(unsigned char *)p == 0x71) {
                *(int *)((char *)s + 8) = v + 12;
            } else if (*(unsigned char *)p == 0x72) {
                *(int *)((char *)s + 8) = v + 12;
            } else if (*(unsigned char *)p == 0x25) {
                *(int *)((char *)s + 8) = v + 8;
            } else if (*(unsigned char *)p == 0x61) {
                *(int *)((char *)s + 8) = v + 12;
            } else {
                *(int *)((char *)s + 8) = v + 8;
            }
        } else if (hit == 1) {
            *(unsigned char *)((char *)D_00270CAC + 0x3B7DA) = 0;
            *(short *)((char *)st + 0x10) = 3;
            break;
        } else {
            if (*(unsigned char *)((char *)D_00270CAC + 0x4C5) == 0) {
                FUN_00117760();
                if ((D_00A98DA3 & 1) != 0) {
                    if (*(int *)((char *)D_00270CAC + 0x49C) != 1) {
                        FUN_00116ad0();
                    }
                }
            }
            v = *(unsigned char *)((char *)D_00270CAC + 0x47D);
            if (v != 0) {
                FUN_00117920();
                v = 1;
            }
            *(int *)((char *)D_00270CAC + 0x4F8) = v;
            *(int *)((char *)D_00270CAC + 0x3554C) = 0;
            *(int *)((char *)D_00270CAC + 0x35550) = 2;
            FUN_00106668(2);
            FUN_001280d0(2);
            *(short *)((char *)st + 0x10) = 2;
            break;
        }
        FUN_00117dc0(st);
        return 0;
    }
    case 2:
        if (FUN_001282f8() != 0) {
            *(unsigned char *)((char *)st + 0xD) = 0;
            break;
        }
        *(short *)((char *)st + 0x10) = 3;
        *(int *)((char *)D_00270CAC + 0x4F8) = 0;
        break;
    case 3: {
        int elem;
        int v;
        int tmp;

        v = *(signed char *)((char *)D_00270CAC + 0x3B7DA);
        FUN_001157f8(*(unsigned short *)((char *)p + 2),
                     *(short *)((char *)D_00270CAC + v * 44 + 0x3B7F8));
        elem = *(int *)((char *)D_00270CAC + v * 44 + 0x3B7F8);
        v = base + elem * 12;
        if (*(unsigned short *)(v + 0xA) != 0xFFFF) {
            if (*(int *)((char *)D_00270CAC + 0x49C) != 1)
                FUN_00115e60(*(int *)((char *)D_00270CAC + 0x52E0),
                             *(unsigned short *)(v + 0xA));
        }
        FUN_00123070();
        FUN_00122d18();
        if (*(int *)((char *)D_00270CAC + 0x49C) != 1)
            FUN_00128340();
        FUN_001283c8();
        v = *(signed char *)((char *)D_00270CAC + 0x3B7DA);
        elem = *(int *)((char *)D_00270CAC + v * 44 + 0x3B7F8);
        tmp = *(int *)(base + elem * 12 + 4);
        s = (int *)*(int *)((char *)st + 0x44);
        if (tmp != -1) {
            *(int *)((char *)s + 8) = *(int *)((char *)s + 0xC) + tmp;
        } else {
            v = *(int *)((char *)s + 8);
            if (*(unsigned char *)p == 0x71) {
                *(int *)((char *)s + 8) = v + 12;
            } else if (*(unsigned char *)p == 0x72) {
                *(int *)((char *)s + 8) = v + 12;
            } else if (*(unsigned char *)p == 0x25) {
                *(int *)((char *)s + 8) = v + 8;
            } else if (*(unsigned char *)p == 0x61) {
                *(int *)((char *)s + 8) = v + 12;
            } else {
                *(int *)((char *)s + 8) = v + 8;
            }
        }
        FUN_00117dc0(st);
        return 0;
    }
    }
    *(unsigned char *)((char *)st + 0xD) = 0;
    *(short *)((char *)st + 0xE) = 0;
    return 0;
}
