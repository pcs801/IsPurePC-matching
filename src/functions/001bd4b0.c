// FUNCTION: SLPM 0x001BD4B0  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00266D78[];
extern char D_00266D98[];

int FUN_001bd4b0(int *p)
{
    int r = 0;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00266D78);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x30);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_00266D98);
    return r;
}
