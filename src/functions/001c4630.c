extern int FUN_001c46a0(int a0);
extern int FUN_001c4670(int a0, int a1);
extern int FUN_001c46a8(void);

void FUN_001c4630(int a0, int a1)
{
    int s0;
    int s1;

    s0 = a0;
    s1 = a1;
    FUN_001c46a0(a0);
    FUN_001c4670(s0, s1);
    FUN_001c46a8();
}
