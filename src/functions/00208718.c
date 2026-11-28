// FUNCTION: SLPM 0x00208718  size 48  core 44
extern int D_0256644;
extern void FUN_002085c8(int, int, int);
extern void FUN_00205d70(int, int);

void FUN_00208718(int a0, int a1)
{
    if (D_0256644 == 0) {
        FUN_00205d70(a0, a1);
        return;
    }
    FUN_002085c8(a0, a1, 1);
}
