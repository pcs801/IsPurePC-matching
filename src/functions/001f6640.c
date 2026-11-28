// FUNCTION: SLPM 0x001F6640
extern int D_00255E88;
extern int FUN_00208ab0(int a0);
extern int FUN_002112c0(int a0);

void FUN_001f6640(void)
{
    D_00255E88 = 0;
    FUN_00208ab0(0x80000018);
    FUN_002112c0(0x80000014);
}
