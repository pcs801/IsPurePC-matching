// FUNCTION: SLPM 0x002032B0  size 144  core 140
extern int FUN_001fc77c(char *a0, char *a1);
extern char D_0026EFF8[];
extern char D_0026EFE8[];

char *FUN_002032b0(char *p, int a1, char *a2)
{
    if (a2 != 0) {
        if (FUN_001fc77c(a2, D_0026EFF8) != 0 && FUN_001fc77c(a2, D_0026EFE8) != 0)
            return 0;
        *(int *)(p + 0x30) = a1;
        *(int *)(p + 0x34) = (int)a2;
    }
    return D_0026EFF8;
}
