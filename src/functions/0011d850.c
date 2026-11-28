extern char *D_00270CAC;
extern void FUN_00117dc0(char *p);

int FUN_0011d850(char *p)
{
    int *q;

    *(short *)(D_00270CAC + 0x492) = 0;
    q = *(int **)(p + 0x44);
    *(int *)((char *)q + 8) = *(int *)((char *)q + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
