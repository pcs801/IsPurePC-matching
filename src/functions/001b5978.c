// FUNCTION: SLPM 0x001B5978  size 48 (core 44)
// *out = FUN_001bd0e0(a, out); return 1;
extern int FUN_001bd0e0(int a, int b);

int FUN_001b5978(int a, int *out)
{
    *out = FUN_001bd0e0(a, (int)out);
    return 1;
}
