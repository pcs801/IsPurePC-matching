extern int FUN_001c67c0(void);
extern int FUN_001c6850(void);
extern int FUN_001c68d8(void);
extern int FUN_001c6900(int a0, int a1);

void FUN_001b25c0(void)
{
    FUN_001c67c0();
}

void FUN_001b25d8(void)
{
    FUN_001c6850();
}

void FUN_001b25f0(void)
{
    FUN_001c68d8();
}

void FUN_001b2608(int a0, int a1)
{
    FUN_001c6900(a0 & 0xFFFF, a1 & 0xFFFF);
}
