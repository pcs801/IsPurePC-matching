// FUNCTION: SLPM 0x0011D4F8  size 80  core 80
extern char *D_00270CAC;
extern void FUN_00117a38(int a0, char *a1, int a2);
extern void FUN_00117dc0(void *p);

int FUN_0011d4f8(char *p)
{
    int *q = *(int **)(p + 68);
    char *r = (char *)q[2];

    FUN_00117a38(r[1], D_00270CAC + 21788, *(int *)(r + 4));
    q = *(int **)(p + 68);
    q[2] = q[2] + 8;
    FUN_00117dc0(p);
    return 0;
}
