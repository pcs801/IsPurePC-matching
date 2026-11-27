// FUNCTION: SLPM 0x0010DCA8  size 160  core 160
extern char D_47B400[];
extern char D_825020[];
extern int D_00270AD0[2];
extern void FUN_001dddf0(void *, void *, int);
extern void FUN_001dde30(void *);
extern void FUN_001df120(int);
extern void FUN_001df138(int);

void FUN_0010dca8(void)
{
    FUN_001dddf0(D_825020, D_47B400, 0x20);
    FUN_001dddf0(D_825020 + 0x10, D_47B400 + 0x1D4E10, 0x20);
    D_00270AD0[0] = (int)(D_47B400 + 0x210);
    D_00270AD0[1] = (int)(D_47B400 + 0x1D5020);
    FUN_001dde30(D_825020);
    FUN_001dde30(D_825020 + 0x10);
    FUN_001df120(1);
    FUN_001df138(0);
}
