extern int D_00270C00;
extern int D_00270C0C;
extern int D_00270C54;
extern int D_00270C58;
extern char D_00D72980[];
extern char D_00212A00[];
extern void FUN_0019ccc0(int a0);
extern void FUN_00102008(void);
extern void FUN_0019daf8(char *a0, char *a1, int a2, int a3);

int FUN_0010e190(void)
{
    if (D_00270C58 != -1)
        FUN_0019ccc0(D_00270C58);
    FUN_00102008();
    D_00270C00 = D_00270C0C;
    D_00270C0C = D_00270C54;
    FUN_0019daf8(D_00212A00 + D_00270C54 * 12, D_00D72980, 0x00E00000, 0);
    return D_00270C54;
}
