extern char D_002561B8[];
extern void FUN_001fbc48(int a0);
extern void FUN_001fb318(int a0, char *a1);
extern void FUN_001fbcc8(int a0);

int FUN_001fb020(char *p)
{
    FUN_001fbc48(*(int *)D_002561B8);
    FUN_001fb318(*(int *)D_002561B8, p);
    FUN_001fbcc8(*(int *)D_002561B8);
    return 0;
}
