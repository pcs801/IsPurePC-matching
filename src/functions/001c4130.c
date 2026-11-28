extern void FUN_001c46a0(void);
extern int FUN_001c4178(int *p, int v);
extern void FUN_001c46a8(void);

int FUN_001c4130(int *p, int v)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c4178(p, v);
    FUN_001c46a8();
    return r;
}
