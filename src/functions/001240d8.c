// FUNCTION: SLPM 0x001240D8  size 64  core 64
extern char *D_00270CB0;

int FUN_001240d8(void)
{
    char *p;
    int v;

    p = D_00270CB0;
    if (*(int *)(p + 0x10) != 0)
        return 0;
    v = *(int *)(p + 0x14);
    if (v == 1)
        return 1;
    if (v != 3)
        return 0;
    return 1;
}
