// FUNCTION: SLPM 0x00209120  size 32  core 28
// NEAR-MISS (1 word, opcode selection): mask value is 0xFFFFFFFE, expressed as
// section address D_FFFF0000 plus literal addend 0xFFFE so ee-gcc emits
// lui v0,0xFFFF + addiu v0,v0,0xFFFE; the target uses ori for the same low half.

extern unsigned int D_FFFF0000;

void FUN_00209120(unsigned int *p)
{
    p[4] &= (unsigned int)&D_FFFF0000 + 0xFFFE;
    p[6] = 0;
}
