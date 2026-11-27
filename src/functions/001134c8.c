// FUNCTION: SLPM 0x001134C8  size 768 (core 764)  -G8
//
// NOT MATCHED - documented analysis only (192 instructions, 0x180 frame).
// Looks like a path/string normaliser feeding a command table:
//   * jal FUN_001fadd8(a0 = s4, 0x3A)   -> strchr(arg, ':') ; s1 = result
//   * copies the prefix into a 0x100-byte stack buffer via FUN_001fcfa0(dst, src, len)
//     and NUL-terminates it (sb zero, len(dst)),
//   * jal FUN_001fc77c(buf, D_0026FEF0) -> strcmp-style compare against a fixed name;
//     when it matches, jumps to the 0x1135E0 tail (scheme specific handling),
//   * jal FUN_001fc9d4(s1 + 1) -> strlen of the remainder; result in t1,
//   * byte loop over the remainder: '/' (0x2F) is rewritten to '\\' (0x5C), then
//     a per-char class table D_0026E701[c] & 2 selects "c - 0x20" (movn) for the
//     stored byte,
//   * jal FUN_001fadd8(s4, 0x3B) and the D_0026FEF8 / D_0026FF10 constants complete
//     the ';' separated argument parsing.
// Byte matching needs the full 0x180-frame layout plus the exact string offsets of
// every table access; out of budget for this round.

void FUN_001134c8(int *a, int *b)
{
    (void)a;
    (void)b;
}
