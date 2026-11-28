// FUNCTION: SLPM 0x001B5BE8
extern void FUN_001b5c70(int);
extern int FUN_001b5c20(int);
extern void FUN_001b5c88(void);

int FUN_001b5be8(int a0)
{
    int r;

    FUN_001b5c70(a0);
    r = FUN_001b5c20(a0);
    FUN_001b5c88();
    return r;
}
