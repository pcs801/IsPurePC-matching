extern void FUN_001c46a0(void);
extern int FUN_001c3b60(int *p, int v);
extern void FUN_001c46a8(void);

int FUN_001c3b18(int *p, int v)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c3b60(p, v);
    FUN_001c46a8();
    return r;
}
