// FUNCTION: SLPM 0x00209120  size 32  core 28
// T2 (change form): the mask is the literal 0xFFFFFFFE (target lui 0xFFFF + ori 0xFFFE),
// not the address of a D_FFFFFFFE symbol (that produced a biased %hi -> lui 0x0000).

void FUN_00209120(unsigned int *p)
{
    p[4] &= 0xFFFFFFFE;
    p[6] = 0;
}
