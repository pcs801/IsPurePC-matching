// FUNCTION: SLPM 0x001bf5d8  size 80  core 76 (two functions in one symbol)
extern int D_002305D8;
extern char D_002677C8[];
extern void FUN_00208450(char *a0);

void FUN_001bf5d8(int a0)
{
    D_002305D8 = a0;
    if (a0 == 1)
        FUN_00208450(D_002677C8);
}

int FUN_001bf618(void)
{
    return D_002305D8;
}
