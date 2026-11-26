// FUNCTION: SLPM 0x001E02D8  size 40
// sig: andi ; addiu ; addiu ; xori ; movz ; andi ; sra ; sra ; jr ; movz

int FUN_001e02d8(int a0, int a1) {
    int size = 0x10;
    if ((a0 & 7) == 3)
        size = 0x100;
    return ((a1 & 7) != 0) ? (size >> 3) : (size >> 2);
}
