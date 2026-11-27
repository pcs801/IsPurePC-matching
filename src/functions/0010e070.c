// FUNCTION: SLPM 0x0010E070  size 288  core 288 (includes 0x0010E128)

extern char D_00258CF8[];
extern char D_00258EB0[];
extern char D_00258EC8[];
extern char D_00258ED8[];
extern char D_00258EE8[];
extern char D_00258F00[];

extern unsigned int D_00270AC8;
extern int D_00270C14;
extern int D_00270C2C;
extern unsigned int D_00270C34;
extern int D_00270C8C;

extern int FUN_0010bf20(void *, ...);
extern void FUN_001076b8(void);
extern void FUN_00107610(void);
extern void FUN_001075d0(void);
extern void FUN_0010d268(void);
extern int FUN_001a9920(void);
extern int FUN_001fbd78(void *, ...);
extern int FUN_002089d0(void);
extern int FUN_0020f730(int, int, int, int);
extern int FUN_002059e0(int);

int FUN_0010e070(void)
{
    if (FUN_001a9920() != 0) {
        FUN_001fbd78(D_00258F00);
        return 1;
    }
    FUN_0010bf20(D_00258EB0);
    FUN_0010bf20(D_00258CF8);
    FUN_001076b8();
    FUN_0010bf20(D_00258EC8);
    FUN_00107610();
    FUN_0010bf20(D_00258ED8);
    FUN_001075d0();
    FUN_0010bf20(D_00258EE8);
    FUN_0010d268();
    FUN_002089d0();
    FUN_0020f730(0x100008, 0, 0, 0);
    return 0;
}

void FUN_0010e128(void)
{
    D_00270C14 = 1;
    FUN_002059e0(D_00270C8C);
    D_00270AC8 = D_00270AC8 < 1;
    while (D_00270C14 == 1)
        ;
    D_00270C2C = 0;
    D_00270C34 = D_00270C34 < 1;
}