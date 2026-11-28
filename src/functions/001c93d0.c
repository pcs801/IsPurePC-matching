// FUNCTION: SLPM 0x001C93D0  size 96  core 84
// if (--*D_00240148 == 0) FUN_001fbb84(D_00240150, 0, 0xC00);
extern char D_00240148[];
extern char D_00240150[];
extern void FUN_001fbb84(char *, int, int);

void FUN_001c93d0(void)
{
    if (--*(int *)D_00240148 == 0)
        FUN_001fbb84(D_00240150, 0, 0xC00);
}
