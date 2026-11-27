// FUNCTION: SLPM 0x001E1D60  size 48  core 40
// NEAR-MISS 4 words: target materialises the constants in the order
//   li v1,7 / srl v0,a0,28 / bne / lui v0,0xfff(delay) / lui v1,0x8000 / ori / and a0 / or a0
// while ee-gcc hoists `lui a1,0xfff` before the compare and uses v1 as the temp.
unsigned int FUN_001e1d60(unsigned int x)
{
    if ((x >> 28) == 7)
        x = (x & 0x0FFFFFFF) | 0x80000000;
    return x;
}
