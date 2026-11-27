// FUNCTION: SLPM 0x0011ABF8  size 1544 (core 1544)  -G8
//
// NOT MATCHED - documented analysis only (disassembly in
// build/m26-tu/tu_00117760/_dis11abf8.txt, 386 instructions, 24 calls).
//
// One function: addiu sp,-0x80; saves s0-s5 + ra; frame holds a local int array
// (up to lbu 1(s3) entries, addressed from $sp).
//
// Shape:
//   st = (unsigned char *)D_00270CAC;            /* lw t0,-0x6D44(gp) */
//   if (st[0x479]) branch to tail;                    /* bnez v0,0x11B1D0 */
//   o   = *(int *)(obj + 0x44);                  /* sub-structure */
//   ph  = *(short *)(obj + 0x10);
//   s3  = *(int *)(o + 8);                       /* entry descriptor block */
//   s5  = *(int *)(o + 0xC) + *(int *)(s3 + 4);  /* base of the 12-byte records */
//   switch (ph) { case 0: ... case 1: ... case 2: ... case 3: ... }
//     - ph == 0 path first checks st[0x4FC] / st[0x4C5] and may call FUN_001161c0().
//   Then per-phase body: FUN_001157f8(lhu 2(s3), -1), store 0 to st[0x4D8].
//   Type dispatch on *s3: 0x72 -> FUN_001058a8(st[0x52E0], lhu 0xA(s3)) and publish
//   two words at (0x40000 + st - 0x481C / - 0x4820); otherwise zero both.
//   Then a Fisher-Yates shuffle over the stack array: n = lbu 1(s3),
//   for (i = 0; i < n; i++) { r = FUN_001fbe00() % n; swap(a[i], a[r]); }
//   (the div-by-zero guard appears as beqzl v1 / break 0,7).
//   Then for (i = 0; i < lbu 1(s3); i++) { j = a[i];
//       if (FUN_00115730(lh 8(s5 + j*12))) { FUN_00115d38(...); FUN_00127f78(j,-1,-1,1);
//                                            FUN_00128328(...); } }
//   Then *s3 type switch (0x71 / 0x72 / 0x25 / 0x61) picks how far the packet cursor
//   (o->f8) advances (+8 / +0xC) before FUN_00117760 / FUN_00117920 / FUN_00106668.
//
// Why it is out of budget: 386 instructions with a stack-array Fisher-Yates, two
// nested type dispatches and 24 calls; byte-exact reconstruction needs the whole
// spill layout, not a local fix.

void FUN_0011abf8(int *obj)
{
    (void)obj;
}