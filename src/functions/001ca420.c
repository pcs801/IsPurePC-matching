// FUNCTION: SLPM 0x001CA420  size 96  core 84
// D_0865780 = a0; D_0865784 = a1; FUN_001c01a8(0x21, D_0865780, 2, D_0865880, 1); return *D_0865880;
extern char D_0865780[];
extern char D_0865880[];
extern void FUN_001c01a8(int, char *, int, char *, int);

int FUN_001ca420(int a0, int a1)
{
    *(int *)D_0865780 = a0;
    *(int *)(D_0865780 + 4) = a1;
    FUN_001c01a8(0x21, D_0865780, 2, D_0865880, 1);
    return *(int *)D_0865880;
}
