// FUNCTION: SLPM 0x00147668  size 520
// best-effort candidate (MISS): target keeps 8 callee-saved regs and lets the
// element pointer be recomputed (a0 = s3 + n*2); this build keeps 9 (fp used
// for the table base) and CSEs the global object pointer differently.
extern char *D_00270BC0;
extern char D_B1EC00[];
extern void FUN_001042b0(void);
extern int FUN_00104648(int);
extern int FUN_00105390(unsigned short);
extern int FUN_00105430(unsigned short);
extern int FUN_00146488(int);
extern void FUN_00178f28(void *, int, int);

void FUN_00147668(void) {
    int i;
    int s7;
    unsigned short n = 0;
    char *b;
    char *s1;
    unsigned short v;

    FUN_001042b0();
    b = D_B1EC00;
    FUN_00146488((int)(D_00270BC0 + 0xDA4));
    s1 = *(char **)(b + 0x68C4);
    {
        char *g = D_00270BC0;
        *(int *)(g + 0x10) = 0;
        *(int *)(g + 0x14) = 0;
    }
    s7 = *(int *)(b + 0x6B88);
    for (i = 0; i < *(int *)(b + 0x68C8); i++) {
        if (FUN_00104648(*(short *)(s1 + 4)) != 0) {
            char *g = D_00270BC0;
            *(unsigned short *)(g + 0x78E0 + n * 0x24 + 0xC) = *(unsigned short *)(s1 + 4);
            *(unsigned short *)(g + 0x78E0 + n * 0x24 + 0xE) = *(unsigned short *)s1;
            *(unsigned short *)(g + 0x78E0 + n * 0x24 + 0x12) = *(unsigned short *)(s1 + 2);
            *(int *)(g + 0x78E0 + n * 0x24 + 0x14) = *(int *)(s7 + ((*(unsigned short *)s1 << 3) & 0x7FF0));
            *(int *)(g + 0x78F8 + n * 0x24) = *(int *)(s1 + 8);
            *(int *)(g + 0x7908 + n * 0x24) = *(int *)(s1 + 0xC);
            *(int *)(g + 0x78FC + n * 0x24) = *(int *)(s7 + ((*(unsigned short *)s1 << 3) & 0x7FF0) + 4);
            *(int *)(g + 0x7900 + n * 0x24) = *(int *)(s7 + ((*(unsigned short *)s1 << 3) & 0x7FF0) + 8);
            *(int *)(g + 0x7904 + n * 0x24) = *(int *)(s7 + ((*(unsigned short *)s1 << 3) & 0x7FF0) + 0xC);
            v = FUN_00105390(*(unsigned short *)(g + 0x78E0 + n * 0x24 + 0xE));
            if (v == 0) {
                *(char *)(g + 0x790E + n * 0x24) = 0;
            } else {
                *(unsigned short *)(g + 0x78E0 + n * 0x24 + 0x10) = v;
                *(char *)(g + 0x790E + n * 0x24) = (FUN_00105430(*(unsigned short *)(g + 0x78E0 + n * 0x24 + 0xE)) == 0);
            }
            *(char *)(g + 0x790F + n * 0x24) = 0;
            *(int *)(g + 0x10) += *(unsigned short *)(g + 0x78F0 + n * 0x24);
            n = n + 1;
        }
        s1 += 0x10;
    }
    *(int *)(D_00270BC0 + 0x14) = n;
    for (i = 7; i >= 0; i--) {
        *(char *)(D_00270BC0 + 0x7900 + i * 0x24 + 0xF) = 1;
    }
    FUN_00178f28(D_00270BC0 + 0xA54, n, 8);
}
