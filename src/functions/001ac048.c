extern char D_00860FC0[];
extern char D_00861000[];
extern int FUN_001ab4b0(void);
extern int FUN_001ac540(char *a0, char *a1, int a2);

void FUN_001ac048(void)
{
    FUN_001ab4b0();
    do {
        FUN_001ac540(D_00860FC0, D_00861000, 100);
    } while (0);
}
