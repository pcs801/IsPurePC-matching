extern int D_00240F2C;
extern void FUN_001c0040(void);

void FUN_001ca760(void)
{
    if (D_00240F2C == 0)
        FUN_001c0040();
    D_00240F2C = D_00240F2C + 1;
}
