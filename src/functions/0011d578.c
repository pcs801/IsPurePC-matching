// FUNCTION: SLPM 0x0011D578  size 56  core 56
extern char *D_00270CAC;
extern void FUN_00117dc0(void *p);

int FUN_0011d578(char *p)
{
    unsigned char *r = (unsigned char *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    *(unsigned char *)(D_00270CAC + 1220) = r[1];
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
