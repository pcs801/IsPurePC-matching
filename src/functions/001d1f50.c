extern int D_00243E6C;
extern void FUN_001d1f90(void);

int FUN_001d1f50(void)
{
    if (D_00243E6C == 0)
        FUN_001d1f90();
    D_00243E6C = D_00243E6C + 1;
    return D_00243E6C;
}
