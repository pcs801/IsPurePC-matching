// FUNCTION: SLPM 0x00123830  size 48  core 44
// *(int*)(D_00270CB0 + idx * 0x5FF8 + 0xA4) = 0xB, idx = *(int*)D_00270CB0
extern char *D_00270CB0;

void FUN_00123830(void)
{
    int idx;

    idx = *(int *)D_00270CB0;
    *(int *)(D_00270CB0 + idx * 0x5FF8 + 0xA4) = 0xB;
}
