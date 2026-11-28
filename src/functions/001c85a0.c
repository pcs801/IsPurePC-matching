extern int D_0023C110;
extern char D_0023C118[];
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001c85a0(void)
{
    if (D_0023C110 == 0)
        FUN_001fbb84(D_0023C118, 0, 16384);
    D_0023C110 = D_0023C110 + 1;
}
