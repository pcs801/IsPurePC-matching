extern int FUN_001c46a0(void);
extern int FUN_001c3948(int a0);
extern int FUN_001c46a8(void);

int FUN_001c3910(int a0)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c3948(a0);
    FUN_001c46a8();
    return r;
}
