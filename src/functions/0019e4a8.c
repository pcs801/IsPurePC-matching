// FUNCTION: SLPM 0x0019E4A8  size 264  core 260  (g=0)
// Jump-table dispatcher over *(s16*)(obj+4), 21 entries at 0x00264BB0:
//   [0]x4 -> 0x19E508 (x4), [1]x3 -> 0x19E4F0 (x3), [2]x2 -> 0x19E4D8 (x2),
//   [19] -> 0x19E540 (x1), [20] -> 0x19E520 (/2), [3..18] 16 entries -> 0x19E54C (shared tail,
//   which is also the >=21 path). Coefficient multiplies a1 * *(int*)(obj+0x24) and
//   accumulates into *(int*)(obj+0x14).
// Status: 264/260, first 41 words exact; the tail differs by 24 words (v1/a1 naming,
// store scheduling and one extra move for the int return value).
int FUN_0019e4a8(char *obj, int a1, int a2)
{
    int idx = *(short *)(obj + 4);
    int t4 = *(int *)(obj + 0x14);
    unsigned short t5 = *(unsigned short *)(obj + 4);
    unsigned short v1, t0, t1;
    int t2, r;
    short r0, r1, r2;

    switch (idx) {
    case 2:
        t4 += (a1 * *(int *)(obj + 0x24)) << 1;
        break;
    case 1: {
        int v = a1 * *(int *)(obj + 0x24);
        t4 += (v << 1) + v;
        break;
    }
    case 0:
        t4 += (a1 * *(int *)(obj + 0x24)) << 2;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        break;
    case 20:
        t4 += (a1 * *(int *)(obj + 0x24)) / 2;
        break;
    case 19:
        t4 += a1 * *(int *)(obj + 0x24);
        break;
    }

    v1 = *(unsigned short *)(obj + 0x24);
    t2 = a2 & 0xFFFF;
    t0 = *(unsigned short *)(obj + 0x1C);
    t1 = *(unsigned short *)(obj + 0x20);
    r0 = *(short *)(obj + 0);
    r1 = *(short *)(obj + 0x0E);
    r2 = *(short *)(obj + 0x10);
    r = (v1 + 63) >> 6;
    *(int *)(obj + 0x28) = t2;
    *(short *)(obj + 0) = r0;
    *(short *)(obj + 4) = t5;
    *(short *)(obj + 2) = (short)r;
    *(short *)(obj + 0x0E) = r1;
    *(short *)(obj + 0x10) = r2;
    *(int *)(obj + 0x14) = t4;
    *(int *)(obj + 0x1C) = t0;
    *(int *)(obj + 0x20) = t1;
    *(int *)(obj + 0x24) = v1;
    *(short *)(obj + 6) = t0;
    *(short *)(obj + 8) = t1;
    *(short *)(obj + 0x0A) = v1;
    *(short *)(obj + 0x0C) = t2;
    return r;
}