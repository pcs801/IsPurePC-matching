// FUNCTION: SLPM 0x0010CAC8  size 344  core 340

extern char D_A94700[];
extern char D_B25810[];
extern int D_00270C74;

void FUN_0010cac8(int a0, int a1)
{
    int attr;
    signed char a, b;
    long long t1, t2;

    attr = (*(int *)(D_B25810 + a1 * 40) & 0x1FF) | 0x1400;
    if (D_00270C74 == 0) {
        a = *(signed char *)(D_A94700 + 0x4697);
        b = *(signed char *)(D_A94700 + 0x4696);
        t1 = ((long long)(0x33 - a) << 12) | (b * 4 + 0x27C) | 0x1BF9FFFF01800000LL;
        t2 = ((long long)(0x32 - a) << 12) | (b * 4 + 0x27C) | 0x1BF9FFFF01800000LL;
        *(long long *)0x12000000 = ((long long)a0 << 8) | 0x23;
        *(long long *)0x12000090 = attr;
        *(long long *)0x120000A0 = t2;
        *(long long *)0x12000070 = attr;
        *(long long *)0x12000080 = t1;
        *(long long *)0x120000D0 = 0;
    } else {
        a = *(signed char *)(D_A94700 + 0x4697);
        b = *(signed char *)(D_A94700 + 0x4696);
        t2 = ((long long)(0x32 - a) << 12) | (b * 2 + 0x138) | 0x1BF4FFFF00800000LL;
        *(long long *)0x12000090 = attr;
        *(long long *)0x120000A0 = t2;
        *(long long *)0x12000070 = attr;
        *(long long *)0x12000080 = t2;
        *(long long *)0x120000D0 = 0;
    }
}
