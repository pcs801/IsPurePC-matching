// FUNCTION: SLPM 0x001BD570  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00266DF8[];
extern char D_00266E18[];

int FUN_001bd570(int *p)
{
    int r = 0;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00266DF8);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x38);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_00266E18);
    return r;
}
