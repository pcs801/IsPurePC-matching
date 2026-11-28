extern char *D_00270CAC;
extern void FUN_00117dc0(char *p);

int FUN_0011d6e0(char *p)
{
    int *q = *(int **)(p + 0x44);
    char *e = *(char **)((char *)q + 8);

    *(short *)(D_00270CAC + 0x4CC) = *(unsigned short *)(e + 2);
    *(int *)((char *)q + 8) = (int)(e + 4);
    FUN_00117dc0(p);
    return 0;
}
