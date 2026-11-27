// FUNCTION: SLPM 0x00111CC0  size 168  core 164
// 164/164 bytes，36 字差：p 的副本落在 $t2（原码 $t1）、a1 被搬到 $t4，整段后续错位
int FUN_00111cc0(char *p, int *a1, int *a2, int *a3, int *t0)
{
    int t4;
    int t3;
    int v;

    if (*(int *)(p + 0x00) == 0) {
        int off = *(int *)(p + 0x2C);

        *a2 = 0x28 - off;
        *a1 = (int)(p + off + 4);
        *t0 = *(int *)(p + 0x3C);
        *a3 = *(int *)(p + 0x30);
        return *(int *)(p + 0x3C);
    }
    t4 = *(int *)(p + 0x3C) - *(int *)(p + 0x34);
    t3 = *(int *)(p + 0x3C) - *(int *)(p + 0x38);
    v = *(int *)(p + 0x30) + *(int *)(p + 0x34);
    if (t4 >= t3) {
        *a2 = t3;
        *a1 = v;
        *t0 = 0;
        *a3 = 0;
        return v;
    }
    *a2 = t4;
    *a1 = v;
    *a3 = *(int *)(p + 0x30);
    *t0 = t3 - t4;
    return *t0;
}