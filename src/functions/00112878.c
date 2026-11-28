// FUNCTION: SLPM 0x00112878  size 48  core 44
// jal FUN_00111238 ; jal FUN_001139e8(D_01B7E4F0) ; return 1
extern void FUN_00111238(void);
extern void FUN_001139e8(int);
extern char D_01B7E4F0[];

int FUN_00112878(void)
{
    FUN_00111238();
    FUN_001139e8((int)D_01B7E4F0);
    return 1;
}
