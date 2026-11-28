extern int D_00243E40;
extern void FUN_001d1f50(void);

int FUN_001d0b38(void)
{
    if (D_00243E40 == 0)
        FUN_001d1f50();
    D_00243E40 = D_00243E40 + 1;
    return D_00243E40;
}
