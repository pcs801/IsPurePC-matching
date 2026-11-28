// FUNCTION: SLPM 0x001BD078  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00266B60[];
extern char D_00266B80[];

int FUN_001bd078(int *p)
{
    int r = 3;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00266B60);
        return 3;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x2C);
    if (f != 0)
        r = f(*(int *)((char *)p + 4));
    else
        FUN_001bc358(D_00266B80);
    return r;
}
