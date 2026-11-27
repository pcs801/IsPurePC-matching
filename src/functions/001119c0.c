// FUNCTION: SLPM 0x001119C0  size 272  core 272
// 272/272 bytes, 仅尾声 3 字差异（原码 ld $s1 排在两条 sw 之前，本工具链排在其后）
extern char D_00259220[];
extern char D_00259258[];
extern char D_00259398[];

int FUN_001119c0(char *p, int delta)
{
    int r;

    if (*(int *)(p + 0x00) == 0) {
        unsigned int cur = *(int *)(p + 0x2C);
        unsigned int need = 0x28 - cur;

        if (need >= (unsigned int)delta)
            need = delta;
        cur += need;
        delta -= need;
        *(int *)(p + 0x2C) = cur;
        if (cur >= 0x28) {
            *(int *)(p + 0x00) = 1;
            FUN_001fbd78(D_00259220);
            FUN_001fbd78(D_00259258, *(signed char *)(p + 4), *(signed char *)(p + 5),
                         *(signed char *)(p + 6), *(signed char *)(p + 7),
                         *(int *)(p + 8), *(int *)(p + 0xC), *(int *)(p + 0x10),
                         *(int *)(p + 0x14), *(int *)(p + 0x18),
                         *(int *)(p + 0x1C), *(int *)(p + 0x20));
            FUN_001fbd78(D_00259398, *(signed char *)(p + 0x24), *(signed char *)(p + 0x25),
                         *(signed char *)(p + 0x26), *(signed char *)(p + 0x27),
                         *(int *)(p + 0x28));
        }
    }
    *(int *)(p + 0x34) = (*(int *)(p + 0x34) + delta) % *(int *)(p + 0x3C);
    *(int *)(p + 0x38) = *(int *)(p + 0x38) + delta;
    *(int *)(p + 0x40) = *(int *)(p + 0x40) + delta;
    return *(int *)(p + 0x40);
}