// FUNCTION: SLPM 0x0012B628  size 48  core 48
// NEAR-MISS (5 words, 44/48 bytes): all 8 plain-C variants give
//   sll v0,a0,5 / lw v1,gp / addu v0,v0,a0 / sll v0,v0,3 / lui at,0x3 / ori at,at,0xDF10
//   addu v1,v1,v0          <- target: addu a0,v1,v0 (pointer into a0)
//   sw a2,0xC(v1)          <- target: daddu v1,a0 ; sw a1,8(v1) ; jr ; sw a2,0xC(a0)
//   jr ra / sw a1,8(v1)
// i.e. ee-gcc coalesces the two pointer uses into one register; the target keeps a
// second copy (daddu v1,a0) and stores through both. No plain-C lever (pointer copy,
// cast, struct field, register qualifier, statement order) reproduces the copy.

extern unsigned int D_00270CAC;

void FUN_0012b628(unsigned int idx, unsigned int step, unsigned int alpha)
{
    unsigned int off = 0x3DF10 + idx * 264;
    unsigned int *p = (unsigned int *)(D_00270CAC + off);
    p[2] = step;
    p[3] = alpha;
}
