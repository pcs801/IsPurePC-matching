// FUNCTION: SLPM 0x001E1D88  size 56  (MISS 52/52 after padding, 4 words)
// ROM loop: sb zero,0(a0) ; v0-- ; a0++ ; nop ; nop ; bne v0,v1(-1) ; nop
// `while (n-- != 0) *p++ = 0;` gives the closest shape (52/52, 4 words).

void FUN_001e1d88(char *p, int n)
{
    while (n-- != 0)
        *p++ = 0;
}
