extern int D_002542D0;
extern int D_00255E74;
extern char D_0026E280[];
extern char D_0086B998[];
extern void FUN_00208450(char *p);
extern void FUN_001f63c8(int a0, int a1, int a2, int a3, char *a4);

void FUN_001f62d8(void)
{
    D_00255E74 = 0;
    if (D_002542D0 > 0)
        FUN_00208450(D_0026E280);
    FUN_001f63c8(0, 0, 0, 7, D_0086B998);
}
