// FUNCTION: SLPM 0x001DD010  size 1680 (core 1676)  GS texture-format dispatcher
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct { u64 lo, hi; } V16;

extern int GsGetIMR(void);
extern void GsPutIMR(int);
extern int FUN_00208450(char *);
extern char D_0026BE20[], D_0026BE58[], D_0026BE88[], D_0026BEC8[];
extern u64 D_00249CC0[2];

int FUN_001dd010(char *desc, char *dst)
{
    u64 t1 = *(u64 *)(desc + 0x40);
    u64 t2 = *(u64 *)(desc + 0x20);
    int w = (int)t1 & 0xFFF;
    int h = (int)(t1 >> 32) & 0xFFF;
    int psm = (int)(t2 >> 24) & 0x3F;
    int a1 = 0, s1 = 0, s2 = 0, s3 = 0, s6 = 0, s0 = 0;
    int v0, v1, a2;
    int i;
    u32 imr;

    switch (psm) {
    case 0:
    case 48:
        a2 = w * h * 4;
        v1 = a2 >> 4;
        s3 = a2 & 0xF;
        s2 = v1 & ~7;
        s1 = v1 & 7;
        if (s3) {
            a1 = (h + 3) & 0x1FFC;
            s6 = ((w * a1) >> 2) - s2 - s1 - 1;
        } else {
            a1 = h;
            s6 = 0;
        }
        break;
    case 1:
    case 49:
        a1 = w * h;
        a2 = 3 * a1;
        v1 = a2 >> 4;
        s3 = a2 & 0xF;
        s2 = v1 & ~7;
        s1 = v1 & 7;
        if (s3) {
            a1 = (h + 15) & 0x1FF0;
            s6 = ((3 * (w * a1)) >> 4) - s2 - s1 - 1;
        } else {
            a1 = h;
            s6 = 0;
        }
        break;
    case 2:
    case 10:
    case 50:
    case 58:
        v1 = w * h;
        a2 = 2 * v1;
        v0 = a2 >> 4;
        s3 = a2 & 0xF;
        s2 = v0 & ~7;
        s1 = v0 & 7;
        if (s3) {
            a1 = (h + 7) & ~7;
            s6 = ((w * a1) >> 3) - s2 - s1 - 1;
        } else {
            a1 = h;
            s6 = 0;
        }
        break;
    case 19:
    case 27:
        a2 = w * h;
        v0 = a2 >> 4;
        s3 = a2 & 0xF;
        s2 = v0 & ~7;
        s1 = v0 & 7;
        if (s3) {
            a1 = (h + 7) & ~7;
            s6 = ((w * a1) >> 4) - s2 - s1 - 1;
        } else {
            a1 = h;
            s6 = 0;
        }
        break;
    case 20:
    case 36:
    case 44:
        v0 = w * h;
        v1 = v0 >> 5;
        a2 = v0 >> 1;
        s3 = a2 & 0xF;
        s2 = v1 & ~7;
        s1 = v1 & 7;
        if (s3) {
            a1 = (h + 7) & ~7;
            s6 = ((w * a1) >> 5) - s2 - s1 - 1;
        } else {
            a1 = h;
            s6 = 0;
        }
        break;
    }

    if (s3)
        *(u64 *)(0x20000000u | (u32)(desc + 0x40)) = ((u64)a1 << 32) | (*(u64 *)(desc + 0x40) & 0xFFF);

    while (*(u32 *)0x10009000 & 0x100) {
        if (++s0 > 0x1000000u) {
            FUN_00208450(D_0026BE20);
            return -1;
        }
    }

    imr = GsGetIMR();
    GsPutIMR(imr | 0x200);
    *(u64 *)0x12001000 = 2;
    *(u32 *)0x10009020 = 7;
    *(u32 *)0x10009010 = ((u32)desc & 0x70000000u) == 0x70000000u
        ? (((u32)desc & 0x0FFFFFFFu) | 0x80000000u) : ((u32)desc & 0x0FFFFFFFu);
    *(u32 *)0x10009000 = 0x101;

    while (*(u32 *)0x10009000 & 0x100) {
        if (++s0 > 0x1000000u) {
            FUN_00208450(D_0026BE58);
            return -1;
        }
    }
    while (!(*(u32 *)0x12001000 & 0x2)) {
        if (++s0 > 0x1000000u) {
            FUN_00208450(D_0026BEC8);
            return -1;
        }
    }

    *(u32 *)0x10003C00 = 0x800000;
    *(u64 *)0x12001040 = 1;
    *(u32 *)0x10009020 = s2;
    *(u32 *)0x10009010 = ((u32)dst & 0x70000000u) == 0x70000000u
        ? (((u32)dst & 0x0FFFFFFFu) | 0x80000000u) : ((u32)dst & 0x0FFFFFFFu);
    *(u32 *)0x10009000 = 0x100;

    while (*(u32 *)0x10009000 & 0x100) {
        if (++s0 > 0x1000000u) {
            FUN_00208450(D_0026BE88);
            return -1;
        }
    }

    for (i = 0; i < s1; i++) {
        while (*(u32 *)0x10003C00 & 0x1F000000) {
        }
        *(V16 *)(dst + (s2 + i) * 16) = *(V16 *)0x10005000;
    }
    if (s3) {
        V16 t = *(V16 *)0x10005000;
        for (i = 0; i < s3; i++)
            dst[(s2 + s1) * 16 + i] = ((u8 *)&t)[i];
    }
    for (i = 0; i < s6; i++) {
        while (*(u32 *)0x10003C00 & 0x1F000000) {
        }
        (void)*(V16 *)0x10005000;
    }

    *(u32 *)0x10003C00 = 0;
    GsPutIMR(imr);
    *(u64 *)0x12001040 = 0;
    *(u64 *)0x12001000 = 2;
    *(V16 *)0x10005000 = *(V16 *)D_00249CC0;
    return 0;
}
