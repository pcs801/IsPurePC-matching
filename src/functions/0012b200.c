// FUNCTION: SLPM 0x0012B200  size 48  core 44
extern char *D_00270CAC;

char *FUN_0012b200(int a0, int a1)
{
    char *p = D_00270CAC + a0 * 264;

    *(int *)(p + 0x3DF04) = a0 != 0 ? a1 : 1;
    return p;
}
