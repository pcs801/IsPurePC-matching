// FUNCTION: SLPM 0x00157780  size 56  core 56
extern int D_00270BD4;
extern int D_00270CAC;
extern int FUN_00156cc8(void);

void FUN_00157780(char *p)
{
    short h = *(short *)(p + 16);
    int *q = *(int **)(p + 68);

    D_00270BD4 = (int)q;
    if (h == 0) {
        q[9] = 0;
        q[0] = 0;
    }
    if (FUN_00156cc8())
        D_00270CAC = 3;
}
