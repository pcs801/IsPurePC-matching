// FUNCTION: SLPM 0x001B5518
extern void FUN_001b5c70(int);
extern int FUN_001b5550(int);
extern void FUN_001b5c88(void);

int FUN_001b5518(int a0)
{
    int r;

    FUN_001b5c70(a0);
    r = FUN_001b5550(a0);
    FUN_001b5c88();
    return r;
}
