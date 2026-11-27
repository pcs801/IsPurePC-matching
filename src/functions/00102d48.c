// FUNCTION: SLPM 0x00102D48  size 1744 (core 1740)
//
// NOT MATCHED - documented analysis only. The card slice covers TWO real functions
// (disassembly kept at build/m26-tu/tu_00100008/_dis2d48.txt, 431 instructions):
//
//   [A] 0x102D48..0x102FB0 (616 B): compaction helper, same family as 0x00102B08.
//       int FUN_00102d48(int start): if (start >= 100) branch to tail;
//       src/dst cursor = &D_A94700[0x46CC + start*0x1EC]; bit map at D_A94700+9
//       accessed as bits+0x46B0; scans 100 slots, on a set bit copies the 0x1EC-byte
//       slot forward (4-byte aligned struct assignment => ldl/ldr/sdl/sdr + lw tail),
//       sets the destination bit, then memsets the leftover slots and publishes the
//       count at D_A94700+0x46B8. Ends with jr ra / addiu sp,+0x40 at 0x102FAC.
//
//   [B] 0x102FB8..0x103414 (1116 B): no stack frame, argument in $a0 (a GS state
//       block), builds GS register words. Switch on the byte at D_A94700+0x46AB
//       ("sltiu v1,v0,5" + jump table at 0x250000+0x7E80 + jr $v1), then a long chain
//       of "lw v1,0x20/0x24(a0); slti ...; ori v0,v0,0x4000/0x2000; sw v0,4(a0)"
//       conditional bit-set sequences ending at 0x10340C (jr ra).
//
// Matching the whole 1740-byte card would require reproducing the switch jump table
// and ~300 instructions of GS register bit programming on top of the compaction
// helper, which is out of reach for this round (20-minute per-function budget).
// Recorded as known-hard; the sibling 0x00102B08 candidate in this TU is the right
// starting point for part [A].

void FUN_00102d48(void)
{
}
