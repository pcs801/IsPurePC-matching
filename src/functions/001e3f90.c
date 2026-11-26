// FUNCTION: SLPM 0x001E3F90  size 24
// sig: lw ; sll ; addu ; jr ; sw ; nop

unsigned int FUN_001e3f90(unsigned int *p, unsigned int idx) {
    unsigned int old = *p;
    *p = old + (idx << 2);
    return old;
}
