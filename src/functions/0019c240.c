// FUNCTION: SLPM 0x0019C240  size 48  core 44
extern char *D_001B9900;

void FUN_0019c240(int a0, int a1, int a2)
{
    char *p = D_001B9900 + a0 * 176;

    *(int *)(p + 0xAC) = a2;
    *(int *)(p) = a1;
}
