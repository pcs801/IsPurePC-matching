extern void FUN_001ce9b8(void);
extern int FUN_001b8790(int *p);
extern void FUN_001ce9c0(void);

int FUN_001b8758(int *p)
{
    int r;

    FUN_001ce9b8();
    r = FUN_001b8790(p);
    FUN_001ce9c0();
    return r;
}
