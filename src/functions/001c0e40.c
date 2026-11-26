// FUNCTION: SLPM 0x001C0E40  size 32
// sig: lw ; lui ; dsrl32 ; dsll ; and ; dsll32 ; jr ; dsra32
// note: 64-bit temp forces dsll + and 0xFFFFFFFF, then (int) forces dsll32/dsra32

int FUN_001c0e40(int *a0) {
    return (int)(((long long)*(int *)((char *)a0 + 0x14) << 11) & 0xFFFFFFFF);
}
