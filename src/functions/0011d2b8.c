// FUNCTION: SLPM 0x0011D2B8  size 60  core 60
extern void FUN_0012d6e8(void *p);
extern void FUN_00117dc0(void *p);

int FUN_0011d2b8(char *p)
{
    int *q;

    FUN_0012d6e8(p);
    q = *(int **)(p + 68);
    q[2] += 4;
    FUN_00117dc0(p);
    return 0;
}
