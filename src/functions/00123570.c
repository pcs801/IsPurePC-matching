extern char *D_00270CAC;
extern char *D_00270CB0;
extern void FUN_001204c0(int v);

void FUN_00123570(void)
{
    int v = 0;

    if (*(unsigned char *)(D_00270CAC + 0x47C) == 1)
        v = 1;
    else if (*(int *)(D_00270CB0 + 0x14) != 0)
        v = 1;
    FUN_001204c0(v);
}
