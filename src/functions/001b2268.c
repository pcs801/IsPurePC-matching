// FUNCTION: SLPM 0x001B2268  size 48 core 44
extern int D_0022E930;
extern void FUN_001c3890(void);
extern void FUN_001c0d48(int);

void FUN_001b2268(int a0)
{
    D_0022E930 = a0;
    FUN_001c3890();
    FUN_001c0d48(a0);
}
