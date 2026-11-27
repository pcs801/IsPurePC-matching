// FUNCTION: SLPM 0x00111D80  size 104  core 100
extern int D_0026FEA4;
extern int FUN_001e9090(int, int, int, int, int, int, int);
extern void FUN_00112260(int);

void FUN_00111d80(char *p)
{
    FUN_001e9090(1, 0x80E0, 1, 0x13, *(int *)(p + 0x44),
                 *(int *)(p + 0x48) / 1024 * 1024,
                 *(int *)(p + 0x44) + *(int *)(p + 0x50));
    *(int *)p = 2;
    FUN_00112260(D_0026FEA4);
}
