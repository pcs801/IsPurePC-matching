extern int FUN_001b5c70(void);
extern int FUN_001b4728(int a0);
extern int FUN_001b5c88(void);

void FUN_001b46f8(int a0)
{
    int s0;

    s0 = a0;
    do {
        FUN_001b5c70();
        FUN_001b4728(s0);
    } while (0);
    FUN_001b5c88();
}
