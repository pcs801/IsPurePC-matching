// FUNCTION: SLPM 0x0020F7A0  size 72  core 72
extern char D_00257A30[];
extern int FUN_0020f610(void *p, int v);
extern void FUN_0020f728(void);
extern void FUN_002055e0(int a0, int a1, int a2);

void FUN_0020f7a0(char *p, int v)
{
    int r = FUN_0020f610(p, v);

    FUN_0020f728();
    FUN_002055e0(r, v, *(int *)D_00257A30 + 4);
}
