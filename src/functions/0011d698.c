extern char *D_00270CAC;
extern void FUN_00117dc0(char *p);

int FUN_0011d698(char *p)
{
    D_00270CAC[0x4C9] = *(unsigned char *)((char *)*(int **)((char *)*(int **)(p + 0x44) + 8) + 1);
    *(int *)((char *)*(int **)(p + 0x44) + 8) = *(int *)((char *)*(int **)(p + 0x44) + 8) + 4;
    FUN_00117dc0(p);
    return 0;
}
