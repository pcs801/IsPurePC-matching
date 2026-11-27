// FUNCTION: SLPM 0x00209120  size 32  core 28
// T3 (symbol restoration): the target materialises the mask as lui 0xFFFF + ori 0xFFFE.
// A symbol at D_FFFEFFFE resolves to that pair under the biased %hi/%lo rule
// (hi = (0xFFFEFFFE + 0x8000) >> 16 = 0xFFFF, lo = 0xFFFE), and the assembled 32-bit
// mask is 0xFFFFFFFE, matching the target's and-mask semantics.

extern unsigned int D_FFFEFFFE;

void FUN_00209120(unsigned int *p)
{
    p[4] &= (unsigned int)&D_FFFEFFFE;
    p[6] = 0;
}
