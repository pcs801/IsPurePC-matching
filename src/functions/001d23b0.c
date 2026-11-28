// FUNCTION: SLPM 0x001D23B0  size 96  core 76
extern char D_0865E7C[];
extern int *FUN_001d22a0(void);

int FUN_001d23b0(int a0, int *a1)
{
    int *r;

    if (*(int *)D_0865E7C == 0)
        return -1;
    r = FUN_001d22a0();
    if (r == 0)
        return -3;
    *a1 = r[3];
    return 0;
}
