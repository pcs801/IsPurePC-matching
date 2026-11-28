extern int FUN_001d2a88(int a0);
extern int FUN_001d2b40(int a0, int a1);
extern int FUN_001d2aa0(void);

int FUN_001d2bf8(int a0, int a1)
{
    int r;

    FUN_001d2a88(a0);
    r = FUN_001d2b40(a0, a1);
    FUN_001d2aa0();
    return r;
}
