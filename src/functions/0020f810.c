extern char D_0026F750[];
extern int D_00257A30;
extern void FUN_0020f610(char *a0, char *a1, int a2);
extern void FUN_0020f728(void);
extern void FUN_00205dc0(char *a0, int a1);

void FUN_0020f810(char *p, int v)
{
    FUN_0020f610(D_0026F750, p, v);
    FUN_0020f728();
    FUN_00205dc0(p, D_00257A30 + 4);
}
