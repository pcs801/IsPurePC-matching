// FUNCTION: SLPM 0x0010DA70  size 272  core 272
extern int D_00270C74;
extern int D_00270C70;
extern int D_00270C18;
extern int D_00270AD0;
extern int D_00270AD4;
extern char D_825020[];
extern char D_47B400[];

extern void FUN_001dc7b8(int, int);
extern void FUN_001dbb18(int, int, int, int);
extern void FUN_0010c320(void);
extern void FUN_001dddf0(void *, void *, int);
extern void FUN_001dde30(void *);
extern void FUN_001df120(int);
extern void FUN_001df138(int);
extern void FUN_001dd6a0(void (*)(void));
extern void FUN_0010df70(void);

void FUN_0010da70(int a0)
{
    int mode = a0;
    int v0;
    int v1;
    int s1;
    int s0;

    D_00270C74 = mode;
    if (mode == 0) {
        v0 = 0x100;
        v1 = 0xDC;
    } else {
        v0 = 0x200;
        v1 = 0x1B8;
    }
    D_00270C70 = v0;
    D_00270C18 = v1;
    if (mode == 0) {
        s1 = 1;
        s0 = 2;
    } else {
        s1 = 0;
        s0 = 0x50;
    }
    FUN_001dc7b8(0, mode);
    FUN_001dbb18(0, s1, s0, 0);
    FUN_0010c320();
    FUN_001dddf0(D_825020, D_47B400, 0x20);
    FUN_001dddf0(D_825020 + 0x10, D_47B400 + 0x1D4E10, 0x20);
    D_00270AD0 = (int)(D_47B400 + 0x210);
    D_00270AD4 = (int)(D_47B400 + 0x1D5020);
    FUN_001dde30(D_825020);
    FUN_001dde30(D_825020 + 0x10);
    FUN_001df120(1);
    FUN_001df138(0);
    FUN_001dd6a0(FUN_0010df70);
}
