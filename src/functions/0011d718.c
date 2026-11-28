// FUNCTION: SLPM 0x0011D718  size 76  core 84 (with padding)
extern char *D_00270CAC;
extern void FUN_001161c0(int a0);
extern void FUN_00117dc0(void *p);

int FUN_0011d718(char *p)
{
    int *q = *(int **)(p + 68);
    unsigned char *r = (unsigned char *)q[2];
    char *g = D_00270CAC;
    unsigned char v = r[1];

    *(unsigned char *)(g + 1221) = v;
    FUN_001161c0(v);
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
