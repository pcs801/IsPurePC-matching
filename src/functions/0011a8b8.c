// FUNCTION: SLPM 0x0011A8B8  size 80  core 80
extern int FUN_001238f8(int a0, int a1);
extern void FUN_00117dc0(void *p);

int FUN_0011a8b8(char *p)
{
    short *r = (short *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    FUN_001238f8(r[2], r[3]);
    q = *(int **)(p + 68);
    q[2] = q[2] + 8;
    FUN_00117dc0(p);
    return 0;
}
