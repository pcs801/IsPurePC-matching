// FUNCTION: SLPM 0x0011A9E8  size 72  core 72
extern char *D_00270CAC;
extern void FUN_00122d18(void *p);
extern void FUN_00117dc0(void *p);

int FUN_0011a9e8(char *p)
{
    char *g;
    int *q;

    FUN_00122d18(p);
    g = D_00270CAC;
    *(unsigned char *)(g + 1276) = 0;
    *(int *)(g + 1240) = 0;
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
