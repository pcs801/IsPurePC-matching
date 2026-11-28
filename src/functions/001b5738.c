extern int FUN_001b5c70(int a0);
extern int FUN_001b5770(int a0);
extern int FUN_001b5c88(void);

int FUN_001b5738(int a0)
{
    int r;

    FUN_001b5c70(a0);
    r = FUN_001b5770(a0);
    FUN_001b5c88();
    return r;
}
