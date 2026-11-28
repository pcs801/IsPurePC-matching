// FUNCTION: SLPM 0x00206C80  size 40  core 36
extern char D_0086CA40[];

char *FUN_00206c80(int v)
{
    *(int *)D_0086CA40 = v;
    *(int *)(D_0086CA40 + 4) = 0;
    *(int *)(D_0086CA40 + 12) = (int)(D_0086CA40 + 16);
    *(int *)(D_0086CA40 + 8) = (int)(D_0086CA40 + 16);
    return D_0086CA40;
}
