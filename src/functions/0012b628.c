// FUNCTION: SLPM 0x0012B628  size 48  core 48
// sig: sll ; lw ; addu ; sll ; lui ; ori ; addu ; addu ; daddu ; sw ; jr ; sw

extern unsigned int D_00270CAC;

void FUN_0012b628(unsigned int idx, unsigned int step, unsigned int alpha) {
    unsigned int off = 0x3DF10 + idx * 264;
    unsigned int *p = (unsigned int *)(D_00270CAC + off);
    p[2] = step;
    p[3] = alpha;
}
