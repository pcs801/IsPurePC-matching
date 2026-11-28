// FUNCTION: SLPM 0x001CBBE8  size 80  core 80
extern int D_00241B70;
extern char D_00241B78[];
extern void FUN_001fbb84(void *a0, int a1, int a2);

void FUN_001cbbe8(void)
{
    if (D_00241B70 == 0)
        FUN_001fbb84(D_00241B78, 0, 768);
    D_00241B70++;
}
