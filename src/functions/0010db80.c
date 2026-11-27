// FUNCTION: SLPM 0x0010DB80  size 112  core 112
extern char D_00258B38[];
extern char D_00258B58[];
extern void FUN_00208eb0(int);
extern void FUN_00208450(void *);
extern int FUN_0020f020(void *);
extern int FUN_0020efd0(void);
extern void FUN_0020dba0(void);
extern void FUN_0020e280(void);

void FUN_0010db80(void)
{
    FUN_00208eb0(0);
    while (FUN_0020f020(D_00258B38) == 0)
        FUN_00208450(D_00258B58);
    while (FUN_0020efd0() == 0)
        ;
    FUN_00208eb0(0);
    FUN_0020dba0();
    FUN_0020e280();
}
