// FUNCTION: SLPM 0x0011CEF0  size 60  core 60
extern void FUN_0012d310(void *p);
extern void FUN_00117dc0(void *p);

int FUN_0011cef0(char *p)
{
    int *q;

    FUN_0012d310(p);
    q = *(int **)(p + 68);
    q[2] += 4;
    FUN_00117dc0(p);
    return 0;
}
