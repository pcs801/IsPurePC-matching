// FUNCTION: SLPM 0x00111F10  size 104  core 100
struct S { int st; };

extern int FUN_001e9090(int, int, int, int, int, int, ...);
extern int FUN_00112260(int);
extern int D_0026FEA4;

int FUN_00111f10(char *q)
{
    struct S *p = (struct S *)q;
    int b = *(int *)(q + 0x48);
    int a = *(int *)(q + 0x44);
    int c = *(int *)(q + 0x50);

    FUN_001e9090(1, 0x80E0, 1, 0x13, a, (b / 1024) * 1024, a + c);
    p->st = 2;
    return FUN_00112260(D_0026FEA4);
}
