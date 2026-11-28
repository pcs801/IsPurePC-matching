extern int D_00240148;
extern char D_00240150[];
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001c9350(void)
{
    if (D_00240148 == 0)
        FUN_001fbb84(D_00240150, 0, 3072);
    D_00240148 = D_00240148 + 1;
}
