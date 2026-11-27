// FUNCTION: SLPM 0x001150B0
extern char D_873F00[];
extern int D_002134F8[];
extern int D_00270CAC;
extern int FUN_0019c2b0(char *, char *);
extern int FUN_0019e328(char *, int, int, char *);

void FUN_001150b0(void)
{
    char *p = D_873F00;
    int *q;
    unsigned int i;

    FUN_0019c2b0(p + ((((*(unsigned int *)p) * 4 + 0x13) >> 4) + *(int *)(p + 0x10)) * 16,
                 (char *)(D_00270CAC + 0xD5680));
    q = D_002134F8;
    for (i = 0; i < 0x13; i++) {
        int t1 = q[0];
        int t2 = q[1];
        q += 2;
        FUN_0019e328((char *)(0xD5300 + D_00270CAC + t1 * 44), 0x2BC0, 0x3D40,
                     (char *)(D_00270CAC + 0xD5680
                              + (((*(int *)(D_00270CAC + 0xD5680) * 4 + 0x13) >> 4)
                                 + *(int *)(D_00270CAC + t2 * 4 + 0xD5684)) * 16));
    }
}
