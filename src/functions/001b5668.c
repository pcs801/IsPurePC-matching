extern int FUN_001b5c70(int a0);
extern int FUN_001b56a0(int a0);
extern int FUN_001b5c88(void);

int FUN_001b5668(int a0)
{
    int r;

    FUN_001b5c70(a0);
    r = FUN_001b56a0(a0);
    FUN_001b5c88();
    return r;
}
