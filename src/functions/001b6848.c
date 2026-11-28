extern void FUN_001ce9b8(void);
extern int FUN_001b6890(int *p, int v);
extern void FUN_001ce9c0(void);

int FUN_001b6848(int *p, int v)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b6890(p, v);
    FUN_001ce9c0();
    return r;
}
