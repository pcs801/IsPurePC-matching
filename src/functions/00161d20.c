// FUNCTION: SLPM 0x00161D20  size 80  core 80
extern int D_00270BE4;
extern void FUN_00161c58(void);
extern void FUN_00155b78(int a0, int a1);

int FUN_00161d20(char *p)
{
    int *q = *(int **)(p + 68);
    short h = *(short *)(p + 16);

    D_00270BE4 = (int)q;
    if (h == 0) {
        FUN_00161c58();
        *(short *)(p + 16) = 1;
    }
    FUN_00155b78(D_00270BE4, 1);
    return 0;
}
