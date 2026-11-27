// FUNCTION: SLPM 0x00111CC0  size 168  core 164
int FUN_00111cc0(char *p, int *a1, int *a2, int *a3, int *t0)
{
    int t4;
    int t3;

    if (*(int *)(p + 0x00) == 0) {
        int off = *(int *)(p + 0x2C);
        int v = *(int *)(p + 0x3C);

        *a2 = 0x28 - off;
        *a1 = (int)(p + off + 4);
        *t0 = v;
        *a3 = *(int *)(p + 0x30);
        return v;
    }
    t4 = *(int *)(p + 0x3C) - *(int *)(p + 0x34);
    t3 = *(int *)(p + 0x3C) - *(int *)(p + 0x38);
    if (t4 < t3) {
        *a2 = t4;
        *a1 = *(int *)(p + 0x30) + *(int *)(p + 0x34);
        *a3 = *(int *)(p + 0x30);
        *t0 = t3 - t4;
        return t3 - t4;
    }
    *a2 = t3;
    *a1 = *(int *)(p + 0x30) + *(int *)(p + 0x34);
    *t0 = 0;
    *a3 = 0;
    return *(int *)(p + 0x30) + *(int *)(p + 0x34);
}
