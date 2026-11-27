// FUNCTION: SLPM 0x0010E008  size 104  core 100

extern char D_00258CF8[];
extern char D_00258EB0[];
extern char D_00258EC8[];
extern char D_00258ED8[];
extern char D_00258EE8[];

extern int FUN_0010bf20(void *, ...);
extern void FUN_001076b8(void);
extern void FUN_00107610(void);
extern void FUN_001075d0(void);

void FUN_0010e008(void)
{
    FUN_0010bf20(D_00258EB0);
    FUN_0010bf20(D_00258CF8);
    FUN_001076b8();
    FUN_0010bf20(D_00258EC8);
    FUN_00107610();
    FUN_0010bf20(D_00258ED8);
    FUN_001075d0();
    FUN_0010bf20(D_00258EE8);
}
