// FUNCTION: SLPM 0x00190030  size 928
typedef unsigned int u32;
typedef unsigned long long u64;
extern int FUN_001fbd78(void *);
extern char D_00263270[];
extern char D_1BA0D50[];

int FUN_00190030(u32 psm, u32 a1, u32 a2, int t8, int t0, int t1)
{
    int s7;
    int t9;
    int fp;

    if (psm >= 0x3B)
        return FUN_001fbd78(D_00263270);
    switch (psm) {
    case 0:
    case 48:
        s7 = t8 << 2;
        break;
    case 1:
    case 49:
        s7 = (t8 << 1) + t8;
        break;
    case 2:
    case 10:
    case 50:
    case 58:
        s7 = t8 << 1;
        break;
    case 19:
    case 27:
        s7 = t8;
        break;
    case 20:
    case 36:
    case 44:
        s7 = (t8 + (t8 >> 31)) >> 1;
        break;
    }
    t9 = 0x7FFC0 / s7;
    if (t0 <= 0)
        return 0;
    for (fp = 0; fp < t0; fp += t9) {
        char *p;
        char *q;
        int tag;
        u64 a2v;
        u64 a1v;

        p = *(char **)(D_1BA0D50 + 0xC);
        q = *(char **)(D_1BA0D50 + 8);
        tag = *(int *)p;
        a2v = fp + t9;
        if (t0 < a2v)
            t9 = t0 - fp;
        *(int *)(tag + 4) = 0;
        switch (psm) {
        case 0: case 1: case 2: case 10: case 27: case 36: case 44: case 48: case 49: case 50: case 58:
            a2 = (t8 + 0x3F) >> 6;
            break;
        case 19: case 20:
            a2 = ((t8 + 0x3F) >> 6) + (((t8 + 0x3F) >> 6) & 1);
            break;
        default:
            a2 = 0;
            break;
        }
        switch (psm) {
        case 0: case 1: case 2: case 10: case 27: case 36: case 44: case 48: case 49: case 50: case 58:
            t1 = (t8 + 0x3F) >> 6;
            break;
        case 19: case 20:
            t1 = ((t8 + 0x3F) >> 6) + (((t8 + 0x3F) >> 6) & 1);
            break;
        default:
            t1 = 0;
            break;
        }
        *(u64 *)(q + 0x20) = ((u64)a2 << 16) | ((u64)(u32)psm << 56) | ((u64)(u32)fp << 32) | ((u64)(u32)t1 << 48);
        *(u64 *)(q + 0x28) = 0x50;
        *(u64 *)(q + 0x30) = (u64)fp << 48;
        *(u64 *)(q + 0x38) = 0x51;
        *(u64 *)(q + 0x40) = ((u64)(u32)t8 << 32) | (u64)(u32)t9;
        *(u64 *)(q + 0x48) = 0x52;
        *(u64 *)(q + 0x50) = 0;
        *(u64 *)(q + 0x58) = 0x53;
        *(int *)(q + 0x60) = 0;
        *(int *)(q + 0x64) = 0x08000000;
        *(int *)(q + 0x68) = 0;
        *(int *)(q + 0x6C) = 0;
        *(int *)(q + 0x70) = 0x30000000 + (int)(((u64)(t9 * s7) + 0xF) >> 4);
        *(int *)(q + 0x74) = 0;
        *(int *)(q + 0x80) = 0x20000002;
        *(int *)(q + 0x84) = 0;
        *(int *)(q + 0x90) = 1;
        *(int *)(q + 0x94) = 0x10000000;
        *(int *)(q + 0x98) = 0xE;
        *(int *)(q + 0x9C) = 0;
        *(u64 *)(q + 0xA0) = 0;
        *(u64 *)(q + 0xA8) = 0x3F;
    }
}
