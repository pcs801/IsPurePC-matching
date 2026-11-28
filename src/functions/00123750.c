// FUNCTION: SLPM 0x00123750  size 40  core 40
// *D_00270CB0 = x ; tail-call FUN_00122fd8(x, x)
extern int *D_00270CB0;
extern void FUN_00122fd8(int, int);

void FUN_00123750(int x)
{
    *D_00270CB0 = x;
    FUN_00122fd8(x, x);
}
