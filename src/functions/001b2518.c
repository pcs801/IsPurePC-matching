extern int FUN_001c6458(void);
extern int FUN_001c66b8(void);
extern int FUN_001c6740(void);
extern int FUN_001c65e0(int a0);

void FUN_001b2518(void)
{
    FUN_001c6458();
}

void FUN_001b2530(void)
{
    FUN_001c66b8();
}

void FUN_001b2548(void)
{
    FUN_001c6740();
}

void FUN_001b2560(int a0)
{
    FUN_001c65e0(*(int *)(a0 + 0xC));
}
