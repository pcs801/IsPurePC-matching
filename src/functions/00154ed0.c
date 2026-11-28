extern int D_00270BCC;
extern int D_00271454;
extern int FUN_00150270(char *p);

void FUN_00154ed0(char *p)
{
    int *q = *(int **)(p + 0x44);

    D_00270BCC = (int)q;
    q[2] = 2;
    if (FUN_00150270(p) != 0)
        D_00271454 = 3;
}
