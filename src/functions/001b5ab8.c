extern int FUN_001b5c70(int a0);
extern int FUN_001b5af8(int a0, int a1);
extern int FUN_001b5c88(void);

void FUN_001b5ab8(int a0, int a1)
{
    int s0;
    int s1;

    s0 = a0;
    s1 = a1;
    FUN_001b5c70(a0);
    FUN_001b5af8(s0, s1);
    FUN_001b5c88();
}
