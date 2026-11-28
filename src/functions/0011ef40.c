extern void FUN_0010ec98(char *p);
extern void FUN_00117dc0(char *p);

int FUN_0011ef40(char *p)
{
    int *q;

    FUN_0010ec98(p);
    q = *(int **)(p + 0x44);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
