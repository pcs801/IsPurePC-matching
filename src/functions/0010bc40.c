// FUNCTION: SLPM 0x0010BC40
extern int FUN_002059e0(int);
extern int FUN_001fbd78(char *);
extern int FUN_0020d520(char *, int, int, int, int, int);
extern int FUN_001f5de0(void *);
extern int FUN_002059d0(int);
extern char D_0026FE18[];
extern char D_0026FE20[];
extern char D_00258A08[];

void FUN_0010bc40(int sema)
{
    for (;;) {
        int x;
        FUN_002059e0(sema);
        FUN_001fbd78(D_00258A08);
        FUN_0020d520(D_0026FE18, 0x5003, 0, 0, 0, 0);
        while (FUN_0020d520(D_0026FE20, 0x4806, 0, 0, 0, 0) < 0)
            ;
        while (FUN_001f5de0(&x) == 0 || x != 0)
            ;
    }
}

void FUN_0010bcd8(int s)
{
    FUN_002059d0(s);
}
