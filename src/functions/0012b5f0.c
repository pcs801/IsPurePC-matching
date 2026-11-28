// FUNCTION: SLPM 0x0012B5F0  size 48  core 44
// *(char*)(D_00270CAC + idx * 0x108 + 0x3DEFE) = v
extern char *D_00270CAC;

void FUN_0012b5f0(int idx, char v)
{
    *(char *)(D_00270CAC + idx * 0x108 + 0x3DEFE) = v;
}
