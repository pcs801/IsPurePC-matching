// FUNCTION: SLPM 0x001E7530  size 56  core 52
extern char D_00253F30[];
extern int FUN_001e7408(int a0, int a1, int a2, int a3);

int FUN_001e7530(int a0, int a1, int a2)
{
    int r = FUN_001e7408(a0, a1, a2, 64);

    if (r == 0)
        *(int *)D_00253F30 = 11;
    return r;
}
