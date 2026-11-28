// FUNCTION: SLPM 0x0012D810  size 368  core 364  (needs hi_bias)
// Two jump tables: 0x259FD0 (8 entries, source select on a0>>12) and
// 0x259FF0 (7 entries, per-source mode byte at 0x1B741F8+n).
extern char *D_00270CAC;
extern char D_001B741F8[];
extern int FUN_001fc2a8(void *buf, void *fmt, int val);
extern int FUN_00101e90(int a0, void *a1, int a2, int a3);
extern int FUN_00101bf0(int a0, void *a1, int a2, int a3);

int FUN_0012d810(unsigned short a0)
{
    unsigned int n = a0 >> 12;
    int off = a0 & 0xFFF;
    int *p = 0;
    char buf[256];
    int v;

    switch (n) {
    case 0:
        n = 0;
        p = *(int **)(0xB1EC4C);
        break;
    case 1:
    case 7:
        n = 1;
        p = *(int **)(0xB1EC54);
        off <<= 1;
        break;
    case 2:
    case 6:
        n = 2;
        p = *(int **)(0xB1EC5C);
        off <<= 1;
        break;
    case 3:
        n = 3;
        p = *(int **)(0xB1EC64);
        off <<= 1;
        break;
    case 4:
        n = 4;
        p = *(int **)(0xB1EC6C);
        break;
    case 5:
        n = 5;
        p = 0;
        break;
    default:
        break;
    }
    if (p == 0)
        return 0;
    v = *(unsigned char *)(0x1B741F8 + n);
    if (v >= 7)
        return 0;
    switch (v) {
    case 0:
    case 2:
    case 4:
    case 6:
        FUN_001fc2a8(buf, (void *)0x270078, p[off]);
        FUN_00101e90(n, buf, *(int *)(D_00270CAC + 0xD5200), *(int *)(D_00270CAC + 0xD5204));
        break;
    case 1:
    case 3:
    case 5:
        FUN_00101bf0(n, buf, *(int *)(D_00270CAC + 0xD5200), *(int *)(D_00270CAC + 0xD5204));
        break;
    }
    return 0;
}