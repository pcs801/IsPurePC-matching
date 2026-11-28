extern int D_0022E938;
extern char D_0022E950[];
extern void FUN_001cc8e0(void);
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001b2980(void)
{
    if (D_0022E938 == 0) {
        FUN_001cc8e0();
        FUN_001fbb84(D_0022E950, 0, 2752);
    }
    D_0022E938 = D_0022E938 + 1;
}
