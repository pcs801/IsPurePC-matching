// FUNCTION: SLPM 0x001BCEF0  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00266AE8[];
extern char D_00266B08[];

int FUN_001bcef0(int *p)
{
    int r = 0;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00266AE8);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x24);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_00266B08);
    return r;
}
