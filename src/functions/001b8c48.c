extern void FUN_001ce9b8(void);
extern int FUN_001b8c80(int *p);
extern void FUN_001ce9c0(void);

int FUN_001b8c48(int *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b8c80(p);
    FUN_001ce9c0();
    return r;
}
