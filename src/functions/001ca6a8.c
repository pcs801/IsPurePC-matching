extern int D_00865780[];
extern char D_00865880[];
extern int FUN_001c01a8(int a0, int a1, int a2, char *a3, int a4);

int FUN_001ca6a8(int a0, int a1)
{
    D_00865780[0] = a0;
    D_00865780[1] = a1;
    FUN_001c01a8(41, (int)D_00865780, 2, D_00865880, 1);
    return *(int *)D_00865880;
}
