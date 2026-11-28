// FUNCTION: SLPM 0x001CF5F0  size 40 (core 36)
extern int D_00242F18;
extern int D_00242F1C;
extern void FUN_001cb6a8(void);

void FUN_001cf5f0(int a, int b)
{
    D_00242F18 = a;
    D_00242F1C = b;
    FUN_001cb6a8();
}
