extern int FUN_001cc4f0(int a0);
extern int FUN_001cc308(int a0, int a1);

void FUN_001b2c38(int a0, int a1)
{
    *(int *)(a0 + 8) = a1;
    FUN_001cc4f0(*(int *)(a0 + 4));
    FUN_001cc308(*(int *)(a0 + 4), a1);
}
