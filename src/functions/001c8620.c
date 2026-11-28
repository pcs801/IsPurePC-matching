// FUNCTION: SLPM 0x001c8620  size 80  core 76
extern int D_0023C110;
extern char D_0023C118[];
extern void FUN_001fbb84(char *a0, int a1, int a2);

void FUN_001c8620(void)
{
    if (--D_0023C110 == 0)
        FUN_001fbb84(D_0023C118, 0, 0x4000);
}
