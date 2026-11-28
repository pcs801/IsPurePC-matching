// FUNCTION: SLPM 0x0011A868  size 80  core 80
extern int FUN_00123990(int a0);
extern void FUN_00117dc0(void *p);

int FUN_0011a868(char *p)
{
    unsigned char *r = (unsigned char *)*(int *)(*(int **)(p + 68) + 2);
    int *q;

    FUN_00123990(r[1]);
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
