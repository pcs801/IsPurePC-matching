// FUNCTION: SLPM 0x0020EFD0  size 96  core 76
extern int FUN_00205db0(int);
extern void FUN_00205e20(void);
extern void FUN_00211318(int, int);

int FUN_0020efd0(void)
{
    if ((FUN_00205db0(4) & 0x40000) != 0) {
        FUN_00205e20();
        FUN_00211318(1, 1);
        FUN_00211318(0, 1);
        return 1;
    }
    return 0;
}
