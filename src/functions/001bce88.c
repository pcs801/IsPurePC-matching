// FUNCTION: SLPM 0x001BCE88  size 104  core 100
extern void FUN_001bc358(char *msg);
extern char D_00266AB0[];
extern char D_00266AD0[];

int FUN_001bce88(int *p)
{
    int r;
    int (*f)(int);

    if (p == 0) {
        FUN_001bc358(D_00266AB0);
        return 0;
    }
    f = *(int (**)(int))((char *)*(int **)p + 0x20);
    if (f != 0) {
        r = f(*(int *)((char *)p + 4));
    } else {
        r = 0;
        FUN_001bc358(D_00266AD0);
    }
    return r;
}
