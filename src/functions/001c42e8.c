extern void FUN_001c46a0(void);
extern int FUN_001c4330(int *p, int v);
extern void FUN_001c46a8(void);

int FUN_001c42e8(int *p, int v)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c4330(p, v);
    FUN_001c46a8();
    return r;
}
