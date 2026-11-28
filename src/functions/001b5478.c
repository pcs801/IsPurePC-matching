// FUNCTION: SLPM 0x001B5478  size 48 (core 44)
// *out = FUN_001b48d0(a, out); return 1;
extern int FUN_001b48d0(int a, int b);

int FUN_001b5478(int a, int *out)
{
    *out = FUN_001b48d0(a, (int)out);
    return 1;
}
