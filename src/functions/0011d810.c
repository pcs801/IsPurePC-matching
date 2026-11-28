// FUNCTION: SLPM 0x0011D810  size 64  core 60
extern char *D_00270CAC;
extern void FUN_00117dc0(void *p);

int FUN_0011d810(char *p)
{
    int *q = *(int **)(p + 68);
    unsigned short v;

    *(unsigned short *)(D_00270CAC + 1172) = 0;
    v = *(unsigned short *)(q[2] + 4);
    q[2] = q[2] + 8;
    *(unsigned short *)(D_00270CAC + 1170) = v;
    FUN_00117dc0(p);
    return 0;
}
