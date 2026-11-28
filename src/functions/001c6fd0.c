// FUNCTION: SLPM 0x001C6FD0  size 48 core 44
extern int D_00238870;
extern int D_00238868;

void FUN_001c6fd0(char *p, int v)
{
    if (D_00238870 != 1 || D_00238868 > 0)
        *(char *)(p + 0x50) = (char)v;
}
