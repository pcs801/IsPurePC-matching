extern char *D_00270BE0;
extern int FUN_00179188(int a0);
extern int FUN_00160770(void);
extern int FUN_0015d2d0(int a0, int a1);
extern int FUN_00179158(int a0, int a1, int a2, int a3);

int FUN_0015bd40(int a0, int a1)
{
    char *g;
    char *h;
    int s0;

    g = D_00270BE0;
    h = (char *)0xC56500;
    *(char *)(g + 0x5E) = 1;
    if (*(int *)(h + 0x10) & 0x10) {
        if (*(int *)(D_00270BE0 + 0x98) != 0 || (*(int *)(h + 8) & 0x10) == 0) {
            FUN_00179158(0, 1, 0, 0);
            return 0;
        }
        FUN_00179188(1);
        g = D_00270BE0;
        *(int *)(g + 8) = *(int *)(g + 0x98);
        *(int *)(g + 0xC) = *(int *)(g + 0x9C);
        FUN_00160770();
        g = D_00270BE0;
        for (s0 = 0; s0 < *(int *)(g + 0xC4); s0++) {
            FUN_0015d2d0(*(int *)(g + 0x14) + s0,
                         (*(int *)(g + 8) - *(int *)(g + 0xC) + s0) % 14);
            g = D_00270BE0;
        }
    }
    return 0;
}
