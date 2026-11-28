// FUNCTION: SLPM 0x001E26E8  size 56  core 52
extern void FUN_001e3b38(int a0);

void FUN_001e26e8(char *p)
{
    int *q = (int *)p;

    FUN_001e3b38(q[2]);
    q[2] = 0;
    q[0] = 0;
    q[1] = 0;
}
