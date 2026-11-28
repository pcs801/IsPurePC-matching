// FUNCTION: SLPM 0x0011D268  size 72  core 72
extern char *D_00270CAC;
extern void FUN_0012d6d0(int a0);
extern void FUN_00117dc0(void *p);

int FUN_0011d268(char *p)
{
    int *q;

    FUN_0012d6d0(*(unsigned short *)(D_00270CAC + 0xD0000 + 20986));
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
