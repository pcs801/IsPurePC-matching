// FUNCTION: SLPM 0x0019B6D8  size 56  core 56
// sig: andi ; andi ; andi ; sll ; or ; andi ; sll ; sll ; or ; lui ; addu ; or

void FUN_0019b6d8(char *base, unsigned i, unsigned lo, unsigned mid, unsigned hi)
{
    unsigned v = (hi & 0xFF);
    unsigned k;
    v <<= 16;
    v |= (lo & 0xFF);
    k = i & 7;
    v |= (mid & 0xFF) << 8;
    v |= 0x80000000u;
    base += k << 2;
    *(unsigned *)(base + 0x38) = v;
}
