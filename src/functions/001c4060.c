extern int FUN_001c46a0(void);
extern int FUN_001c4098(int a0);
extern int FUN_001c46a8(void);

int FUN_001c4060(int a0)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c4098(a0);
    FUN_001c46a8();
    return r;
}
