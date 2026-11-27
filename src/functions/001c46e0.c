// FUNCTION: SLPM 0x001C46E0
extern int D_00232630;
extern int D_00232634;

void FUN_001c46e0(int a0, int a1)
{
    if (a0 == 0) {
        D_00232630 = 0;
        D_00232634 = 0;
    } else {
        D_00232630 = a0;
        D_00232634 = a1;
    }
}
