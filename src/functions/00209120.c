// FUNCTION: SLPM 0x00209120
// The original loads a mask from absolute data symbol D_FFFFFFFE (0xFFFFFFFE).
extern unsigned int D_FFFFFFFE;

void FUN_00209120(unsigned int *p)
{
    p[4] &= (unsigned int)&D_FFFFFFFE;
    p[6] = 0;
}
