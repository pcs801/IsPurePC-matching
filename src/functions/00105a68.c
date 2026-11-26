extern int D_D6E8D0[];
extern int FUN_001fbe00(void);

void FUN_00105a68(void)
{
    unsigned int n;
    unsigned int i;

    n = *(unsigned int *)0x10000000;
    n += D_D6E8D0[4];
    n += D_D6E8D0[5];
    n += D_D6E8D0[6];
    n += D_D6E8D0[7];
    n += D_D6E8D0[8];
    n += D_D6E8D0[9];
    n &= 0xFFFF;
    for (i = 0; i < n; i++)
        FUN_001fbe00();
}
