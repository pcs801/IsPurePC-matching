// FUNCTION: SLPM 0x00111658  size 216  core 216

extern char D_1B7E448[];

extern int FUN_00111cc0(void *, int *, int *, int *, int *);
extern int FUN_00111528(int, int, int, int, int, int, int, int);
extern int FUN_001119c0(void *, int);

int FUN_00111658(int unused, int *s, int base)
{
    int a, b, c, d;
    int v1, s0, s1, s2, r;

    v1 = *(int *)(base + 0x50008);
    s0 = s[2] + 4;
    s1 = base + v1;
    s2 = s[3] - 4;
    if ((unsigned int)s0 >= (unsigned int)s1)
        s0 -= v1;
    s1 -= s0;
    if (s2 < s1)
        s1 = s2;
    FUN_00111cc0(D_1B7E448, &a, &b, &c, &d);
    s2 -= s1;
    r = FUN_00111528(a, b, c, d, s0, s1, base, s2);
    FUN_001119c0(D_1B7E448, r);
    return r > 0;
}