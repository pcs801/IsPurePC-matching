// FUNCTION: SLPM 0x0011A720  size 80  core 80
extern int FUN_00123868(int a0, int a1);
extern void FUN_00117dc0(void *p);

int FUN_0011a720(char *p)
{
    short *r = (short *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    FUN_00123868(r[2], r[3]);
    q = *(int **)(p + 68);
    q[2] = q[2] + 8;
    FUN_00117dc0(p);
    return 0;
}
