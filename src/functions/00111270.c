extern int D_0026FEA0;
extern int D_0026FEA4;
extern int D_0026FEA8;
extern int D_0026FEB8[1];
extern int D_00270CA0;
extern int D_00270CA8;
extern char D_0026FEC0[];
extern char D_00259148[];
extern char D_1B7E200[];
extern char D_1B7E4A8[];
extern char D_1B7E560[];
extern int FUN_001fbd78(void *, ...);
extern int FUN_00205890(void);
extern int FUN_00205830(int, int);
extern void FUN_001dc520(void *, int, int, int, int, int, int);
extern void FUN_00205c20(int);
extern void FUN_00110d30(int);
extern int FUN_00110af8(void *, void *, void *);
extern void FUN_00110fc0(void);
int FUN_00111270(int a0, int a1, int a2, int a3)
{
    int n;

    FUN_001fbd78(D_0026FEC0, 0x672880);
    FUN_001fbd78(D_00259148, D_0026FEB8[0]++);
    D_00270CA0 = a2;
    if (a1 == 0)
        D_0026FEA0 = 0;
    else
        D_0026FEA0 = 1;
    D_0026FEA4 = (a1 * 32767) / 128;
    D_0026FEA8 = a3;

    n = FUN_00205830(FUN_00205890(), 1);
    FUN_001dc520(D_1B7E200, 0, 0x280, 0xF0, 0, 0, 1);
    FUN_00205c20(0);
    FUN_00110d30(a0);
    FUN_00110af8(D_1B7E4A8, (void *)(D_00270CA0 + 0x622800), D_1B7E560);
    FUN_00110fc0();
    FUN_00205830(FUN_00205890(), n);
    return D_00270CA8;
}