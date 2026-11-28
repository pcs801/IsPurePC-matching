// FUNCTION: SLPM 0x001CA6F8  size 120  core 104
extern char D_0865780[];
extern char D_0865880[];
extern void FUN_001c01a8(int, char *, int, char *, int);

int FUN_001ca6f8(int a0, int a1, int a2, int *a3)
{
    int v;

    *(int *)D_0865780 = a0;
    *(int *)(D_0865780 + 4) = a1;
    *(int *)(D_0865780 + 8) = a2;
    FUN_001c01a8(0x2A, D_0865780, 3, D_0865880, 1);
    v = *(int *)(D_0865880 + 4);
    *a3 = v;
    return *(int *)D_0865880;
}
