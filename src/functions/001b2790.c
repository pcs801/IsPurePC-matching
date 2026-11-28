// FUNCTION: SLPM 0x001B2790  size 48 (core 44) - the symbol holds TWO functions:
//   0x001B2790: addiu sp ; sd ra ; ld ra ; j FUN_001c7438 ; addiu sp ; nop
//   0x001B27A8: addiu sp ; sd ra ; ld ra ; j FUN_001c74e0 ; addiu sp ; nop
// Writing both functions in one file reproduces the 44-byte range exactly.

extern int FUN_001c7438(void);
extern int FUN_001c74e0(void);

void FUN_001b2790(void)
{
    FUN_001c7438();
}

void FUN_001b27a8(void)
{
    FUN_001c74e0();
}
