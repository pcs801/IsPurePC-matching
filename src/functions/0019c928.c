// FUNCTION: SLPM 0x0019C928  size 96  core 96
extern char D_1B9F908[];
extern int FUN_001fbb84(void *p, int a1, int a2);

int FUN_0019c928(int *p, int a1)
{
    int *q = (int *)D_1B9F908;
    int v = *p;

    q[0] = (int)(p + 1);
    q[1] = a1;
    q[2] = v;
    q[3] = a1 + v;
    q[4] = 0xFEE;
    q[5] = 0;
    return FUN_001fbb84(q + 6, 0, 0xFEE);
}
