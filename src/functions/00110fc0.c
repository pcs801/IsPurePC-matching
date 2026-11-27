// FUNCTION: SLPM 0x00110FC0  size 176  core 176

extern int D_00270CA0;
extern int D_00270C90;
extern int D_00270C94;
extern int D_00270C98;
extern char D_1B7E4A8[];
extern char D_1B7E448[];
extern char D_1B7E430[];
extern char D_1B7E560[];

extern void FUN_00111760(void *);
extern void FUN_00112b88(void *);
extern void FUN_00112550(void *);
extern void FUN_00111c80(void *);
extern void FUN_001137c8(void *);
extern void FUN_001dd6a0(void (*)(void));
extern int FUN_002057f0(int);
extern int FUN_002057b0(int);
extern int FUN_00206550(int);
extern int FUN_002056d0(int, int);

void FUN_00110fc0(void)
{
    int *hw = (int *)0x1000E000;
    char *tbl;

    tbl = D_1B7E4A8;
    FUN_00111760((void *)(D_00270CA0 + 0x622800));
    FUN_00112b88(D_1B7E430);
    FUN_002057f0(D_00270C98);
    FUN_002057b0(D_00270C98);
    FUN_002057f0(D_00270C94);
    FUN_002057b0(D_00270C94);
    FUN_00206550(2);
    FUN_002056d0(2, *(int *)(tbl + 0xB0));
    FUN_001dd6a0(0);
    FUN_00112550(tbl);
    FUN_00111c80(D_1B7E448);
    FUN_001137c8(D_1B7E560);
    *hw = D_00270C90;
}
