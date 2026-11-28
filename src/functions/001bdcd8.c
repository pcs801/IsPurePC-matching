// FUNCTION: SLPM 0x001BDCD8  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_002671D8[];
extern char D_002671F8[];

int FUN_001bdcd8(int *p)
{
    int r = 0;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_002671D8);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x64);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_002671F8);
    return r;
}
