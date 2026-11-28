// FUNCTION: SLPM 0x0011D0E8  size 72  core 72
extern int FUN_0012d478(int a0);
extern void FUN_00117dc0(void *p);

int FUN_0011d0e8(char *p)
{
    unsigned char *r = (unsigned char *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    FUN_0012d478(r[1]);
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
