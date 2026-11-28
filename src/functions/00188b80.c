extern char D_00270730[];
extern char *FUN_001fd160(int a0, char *a1);

int FUN_00188b80(char *p)
{
    int *q = *(int **)(p + 0x44);
    char *t;

    t = FUN_001fd160(q[6], D_00270730);
    *t = 0;
    q[6] = (int)(t + 2);
    return 1;
}
