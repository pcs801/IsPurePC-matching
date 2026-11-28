// FUNCTION: SLPM 0x001C70B8  size 48 core 44
extern int D_00238870;
extern int D_00238868;

void FUN_001c70b8(char *p, int v)
{
    if (D_00238870 != 1 || D_00238868 > 0)
        *(char *)(p + 0x5B) = (char)v;
}
