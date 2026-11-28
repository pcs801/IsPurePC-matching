extern int FUN_001b5c70(int a0, int a1);
extern int FUN_001b4a18(int a0, int a1);
extern int FUN_001b5c88(void);

int FUN_001b49d0(int a0, int a1)
{
    int r;

    FUN_001b5c70(a0, a1);
    r = FUN_001b4a18(a0, a1);
    FUN_001b5c88();
    return r;
}
