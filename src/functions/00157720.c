// FUNCTION: SLPM 0x00157720  size 96  core 92  -G8
extern char D_002174C8[];
extern int D_00270BD4;
extern int FUN_0019daf8(int a0, int a1, int a2, int a3);

void FUN_00157720(char *p, int a1, int a2)
{
    int q;

    D_00270BD4 = (int)p;
    *(int *)(p + 0x00) = 0;
    *(int *)(p + 0x24) = 0;
    FUN_0019daf8((int)D_002174C8, (int)p, a1, 2);
    q = D_00270BD4;
    *(int *)(q + 0x24) = a2;
    *(int *)(q + 0x00) = 1;
}
