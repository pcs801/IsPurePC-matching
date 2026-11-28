// FUNCTION: SLPM 0x00130FB0  size 48（两个块 = 两函数）
extern char *D_00270CAC;

void FUN_00130fb0(void)
{
    *(int *)(D_00270CAC + 0x4D184) = 0;
}

int FUN_00130fc8(void)
{
    return *(int *)(D_00270CAC + 0x4D184);
}
