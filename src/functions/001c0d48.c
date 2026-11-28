// FUNCTION: SLPM 0x001c0d48  size 80  core 76 (four small functions in one symbol)
extern int D_00231F38;
extern int D_0023123C;

void FUN_001c0d48(int a0)
{
    D_00231F38 = a0;
}

int FUN_001c0d58(void)
{
    return D_00231F38;
}

void FUN_001c0d68(unsigned int a0)
{
    if (a0 < 2)
        D_0023123C = a0;
    else
        D_0023123C = 0;
}

int FUN_001c0d88(void)
{
    return D_0023123C;
}
