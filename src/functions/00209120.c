// FUNCTION: SLPM 0x00209120  size 32  core 28
// DImode OR of the section address with the literal low half.

extern unsigned int D_FFFF0000;

void FUN_00209120(unsigned int *p)
{
    p[4] &= (unsigned int)((unsigned long long)(void *)&D_FFFF0000 | 0xFFFEULL);
    p[6] = 0;
}
