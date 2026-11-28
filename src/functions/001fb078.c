// FUNCTION: SLPM 0x001FB078  size 72  core 72
extern char D_002561B8[];
extern void FUN_001fbc48(int a0);
extern void FUN_002029d0(int a0, void *a1);
extern void FUN_001fbcc8(int a0);

void FUN_001fb078(char *p)
{
    FUN_001fbc48(*(int *)D_002561B8);
    FUN_002029d0(*(int *)D_002561B8, p);
    FUN_001fbcc8(*(int *)D_002561B8);
}
