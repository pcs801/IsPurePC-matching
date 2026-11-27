// FUNCTION: SLPM 0x00209120  size 32  core 28
// Array-typed symbol so the address is materialised through the section-relative path.

extern unsigned int D_FFFF0000[];

void FUN_00209120(unsigned int *p)
{
    p[4] &= (unsigned int)D_FFFF0000 + 0xFFFE;
    p[6] = 0;
}
