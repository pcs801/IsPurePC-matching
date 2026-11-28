// FUNCTION: SLPM 0x001c6e90  size 72  core 72
extern int D_00238870;
extern int D_00238868;
extern char D_00268E20[];
extern void FUN_001b2390(char *a0);

void FUN_001c6e90(void)
{
    if (D_00238870 == 1 && D_00238868 <= 0)
        return;
    FUN_001b2390(D_00268E20);
}
