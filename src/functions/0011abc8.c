// FUNCTION: SLPM 0x0011ABC8  size 48
extern void FUN_00117dc0(char *);

int FUN_0011abc8(char *p)
{
    int q = *(int *)(p + 0x44);

    *(int *)(q + 8) = *(int *)(q + 8) + 8;
    FUN_00117dc0(p);
    return 0;
}
