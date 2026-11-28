// FUNCTION: SLPM 0x0011D468  size 64  core 64
extern char *D_00270CAC;
extern void FUN_00117dc0(void *p);

int FUN_0011d468(char *p)
{
    int *q = *(int **)(p + 68);
    int *r = (int *)q[2];
    unsigned short v = *(unsigned short *)((char *)r + 2);

    q[2] = (int)(r + 1);
    *(unsigned short *)(D_00270CAC + 0x40000 - 3320) = v;
    FUN_00117dc0(p);
    return 0;
}
