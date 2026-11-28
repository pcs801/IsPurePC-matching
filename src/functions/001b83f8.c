extern void FUN_001ce9b8(void);
extern int FUN_001b8430(int *p);
extern void FUN_001ce9c0(void);

int FUN_001b83f8(int *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b8430(p);
    FUN_001ce9c0();
    return r;
}
