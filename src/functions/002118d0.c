// FUNCTION: SLPM 0x002118D0  size 60  core 60
extern int FUN_00205e00(void);
extern void FUN_00211910(void);
extern void FUN_00205e10(void);

void FUN_002118d0(void)
{
    if (FUN_00205e00() == 0x02000000) {
        do {
            FUN_00211910();
        } while (0);
    } else {
        do {
            FUN_00205e10();
        } while (0);
    }
}
