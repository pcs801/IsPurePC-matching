// FUNCTION: SLPM 0x001F7170  size 32  core 32
// sig: andi ; srl ; addiu ; mult ; mflo ; subu ; jr ; andi
// best-effort: semantics = BCD byte -> binary with 6/16 correction.
// ee-gcc 2.96 (-O2 -mips3) always strength-reduces the constant *6 into
// sll/addu/sll, while the ROM kept mult+mflo; see result.json note.

unsigned char FUN_001f7170(unsigned char a0) {
  return a0 - (a0 >> 4) * 6;
}
