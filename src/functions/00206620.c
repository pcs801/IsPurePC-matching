// FUNCTION: SLPM 0x00206620  size 32  (also 0x00206640 / 0x00206660 / 0x00206680)
// ROM: addiu sp,-0x10 ; sd ra,0(sp) ; jal FUN_00208xx0 ; nop ; sync ; ld ra,0(sp) ; jr ra ; addiu sp
// The `sync` (0x0000000F) memory barrier cannot be generated from plain C (no C construct
// emits SYNC; asm is banned in this pipeline), so this whole family is asm-only.
// Same for 0x001AC460 which additionally contains `ei` (0x42000038).

extern volatile int D_duplicate_sync_stub;
