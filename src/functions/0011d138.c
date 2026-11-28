// FUNCTION: SLPM 0x0011D138  size 72  core 72
extern int FUN_0012d4a0(int a0, int a1);
extern void FUN_00117dc0(void *p);

int FUN_0011d138(char *p)
{
    unsigned char *r = (unsigned char *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    FUN_0012d4a0(r[1], *(unsigned short *)(r + 2));
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
