// FUNCTION: SLPM 0x0020F3E8  size 96  core 88
// eight calls (the 4th takes 2), then a tail sibcall to FUN_00211160
extern void FUN_0020f198(void);
extern void FUN_0020f2d8(void);
extern void FUN_0020f8c8(void);
extern void FUN_0020fa40(int);
extern void FUN_0020fc80(void);
extern void FUN_00206778(void);
extern void FUN_0020f510(void);
extern void FUN_00211748(void);
extern void FUN_00211160(void);

void FUN_0020f3e8(void)
{
    FUN_0020f198();
    FUN_0020f2d8();
    FUN_0020f8c8();
    FUN_0020fa40(2);
    FUN_0020fc80();
    FUN_00206778();
    FUN_0020f510();
    FUN_00211748();
    FUN_00211160();
}
