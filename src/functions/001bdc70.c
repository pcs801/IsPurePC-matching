// FUNCTION: SLPM 0x001BDC70  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00267198[];
extern char D_002671B8[];

int FUN_001bdc70(int *p)
{
    int r = 0;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00267198);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x60);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_002671B8);
    return r;
}
