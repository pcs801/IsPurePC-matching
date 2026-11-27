// FUNCTION: SLPM 0x0010D788  size 696  core 696
extern int D_00270C58;
extern int D_00270C54;
extern int D_00270C0C;
extern int D_00270C00;
extern unsigned int D_00270C34;
extern int D_00270AD0[];
extern int D_00270C88;
extern int D_00270C80;
extern int D_00270C4C;
extern int D_00270C08;
extern int D_00270C8C;
extern unsigned int D_00270AC8;
extern int D_00270C14;
extern int D_00270C2C;
extern int D_00270C40;
extern char D_D72980[];
extern char D_00212A00[];
extern char D_825020[];
extern char D_00258F18[];

extern void FUN_001f8758(void);
extern void FUN_0010cc20(void);
extern void FUN_0010d320(void);
extern void FUN_0019ccc0(void);
extern int FUN_0019daf8(void *, void *, int, int);
extern void FUN_00102008(void);
extern int FUN_001dc850(int, int);
extern void FUN_00105fb8(void *);
extern void FUN_001fbe00(void);
extern void FUN_001b1af0(void);
extern void FUN_001dde30(void *);
extern void FUN_0019ec30(int, void *);
extern void FUN_0019b688(void *);
extern void FUN_0019b710(void *, int, int);
extern void FUN_0017ef80(void);
extern void FUN_00108478(int, int, int);
extern void FUN_00101960(int);
extern void FUN_001a9860(int, int);
extern void FUN_001a9840(int);
extern void FUN_001a9850(int);
extern void FUN_002059e0(int);
extern void FUN_00205c20(int);
extern int FUN_001de098(void *, int);
extern void FUN_001fbd78(void);

void FUN_0010d788(void)
{
    FUN_001f8758();
    FUN_0010cc20();
    FUN_0010d320();

    D_00270C54 = 2;
    D_00270C0C = 2;
    if (D_00270C58 != -1)
        FUN_0019ccc0();
    FUN_00102008();
    D_00270C00 = D_00270C0C;
    D_00270C0C = D_00270C54;
    D_00270C58 = FUN_0019daf8(D_00212A00 + D_00270C54 * 12, D_D72980, 0xE00000, 0);
    FUN_001dc850(0, 0);
    *(int *)0x10000000 = 0;

    for (;;) {
        FUN_00105fb8(D_00258F18);
        FUN_001fbe00();
        FUN_001b1af0();
        D_00270C88 = (int)(D_825020 + D_00270C34 * 16);
        D_00270C80 = D_00270AD0[D_00270C34];
        FUN_001dde30((void *)D_00270C88);
        FUN_0019ec30(D_00270C88, &D_00270C80);
        FUN_0019b688((void *)D_00270C4C);
        FUN_0019b710((void *)D_00270C4C, 0, 0);
        if (((int (*)(int)) * (int *)0x1BA0938)(D_00270C58)) {
            if (D_00270C58 != -1)
                FUN_0019ccc0();
            FUN_00102008();
            D_00270C00 = D_00270C0C;
            D_00270C0C = D_00270C54;
            D_00270C58 = FUN_0019daf8(D_00212A00 + D_00270C54 * 12, D_D72980, 0xE00000, 0);
        }
        FUN_0017ef80();
        FUN_00108478(0xFF, 0xFF, 0xFF);
        FUN_00101960(-1);
        FUN_00108478(0, 0xFF, 0);
        FUN_001a9860(D_00270C80 - D_00270AD0[D_00270C34], 0x1D4C00);
        FUN_001a9840(D_00270C08);
        FUN_001dc850(0, 0);
        FUN_00108478(0x40, 0x40, 0x40);
        FUN_001a9850(*(int *)0x10000000);
        D_00270C14 = 1;
        FUN_002059e0(D_00270C8C);
        D_00270AC8 = D_00270AC8 < 1;
        while (D_00270C14 == 1)
            ;
        D_00270C2C = 0;
        D_00270C34 = D_00270C34 < 1;
        FUN_00205c20(0);
        *(int *)0x10000000 = 0;
        while (FUN_001de098((void *)D_00270C88, 2) < 0)
            FUN_001fbd78();
        D_00270C40++;
    }
}
