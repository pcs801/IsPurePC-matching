// FUNCTION: SLPM 0x0010DD48  size 376  core 376 (includes 0x0010DE10)

extern char D_47B400[];
extern char D_825020[];
extern int D_00270AD0;
extern int D_00270AD4;
extern int D_00258B70[];
extern int D_00258B88[];
extern int D_00258BB0[];

extern void FUN_001dbcb8(void);
extern void FUN_001e1de8(int);
extern void FUN_001dbb18(int, int, int, int);
extern void FUN_0010c320(void);
extern void FUN_001dddf0(void *, void *, int);
extern void FUN_001dde30(void *);
extern void FUN_001df120(int);
extern void FUN_001df138(int);
extern int FUN_0010bf20(void *, ...);
extern int FUN_001fe618(int);
extern int FUN_001fc2a8(char *, void *, int);
extern int FUN_0020eaf0(char *, int, int);
extern int FUN_001dc850(int, int);

void FUN_0010dd48(void)
{
    FUN_001dbcb8();
    FUN_001e1de8(1);
    FUN_001dbb18(0, 1, 2, 0);
    FUN_0010c320();
    FUN_001dddf0(D_825020, D_47B400, 0x20);
    FUN_001dddf0(D_825020 + 0x10, D_47B400 + 0x1D4E10, 0x20);
    {
        int t0 = (int)(D_47B400 + 0x210);
        int t1 = (int)(D_47B400 + 0x1D5020);
        D_00270AD0 = t0;
        D_00270AD4 = t1;
    }
    FUN_001dde30(D_825020);
    FUN_001dde30(D_825020 + 0x10);
    FUN_001df120(1);
    FUN_001df138(0);
}

void FUN_0010de10(int *p)
{
    char buf[0x100];
    int i;
    int r;

    i = 0;
    FUN_001fe618(p[0]);
    FUN_001fc2a8(buf, D_00258B70, p[0]);
    while ((p[3] = FUN_0020eaf0(buf, p[1], p[2])) < 0) {
        FUN_0010bf20(D_00258B88, i++, buf, p[3]);
        FUN_001dc850(0, 0);
    }
    FUN_0010bf20(D_00258BB0, p[3], p[0]);
}