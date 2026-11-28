// FUNCTION: SLPM 0x001AC080  size 56  core 56
extern char D_00860FC0[];
extern char D_00861000[];
extern int FUN_001ab4b0(void);
extern int FUN_001ac540(void *a0, void *a1, int a2);

void FUN_001ac080(int p)
{
    FUN_001ab4b0();
    *(int *)D_00861000 = p;
    FUN_001ac540(D_00860FC0, D_00861000, 101);
}
