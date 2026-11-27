// FUNCTION: SLPM 0x001DCB68  size 488 (core 484)  -- 59-way coefficient select + fixed VU microcode
// Params: p = a0 (packet base, t6), then SEVEN shorts (a1,a2,a3,t0,t1,t2,t3) - the target
// sign-extends every one of them with sll 16 / sra 16.
// switch on the 4th short (t5): table 0x0026BCF0, 59 entries, only 5 distinct targets:
//   [0]      -> 0x1DCBD4  coeff = (s6 * s7) >> 2
//   [1]      -> 0x1DCBE0  coeff = (s6 * s7 * 3) >> 4
//   [2][10]  -> 0x1DCBF4  coeff = (s6 * s7) >> 3
//   [19][27] -> 0x1DCC00  coeff = (s6 * s7) >> 4
//   [20][36] -> 0x1DCC0C  coeff = (s6 * s7) >> 5
//   other 46 -> 0x1DCC14  coeff stays 0   (write ONLY these 5 groups; 59 explicit cases
//                                          would be folded into a range check)
// Guard: if (coeff > 0x7FFF) { FUN_00208450(D_0026BCC0); return 0; }
// Microcode: 128-bit zero stores at +0x50/+0x00, then eleven 64-bit RMW stores at
// 0x00/0x08/0x10/0x18/0x20/0x28/0x30/0x38/0x40/0x48/0x50 with masks 0xFFFF8000,
// 0x0FFFFFFFFFFFFFFF, ~0xF, 0xF3FFFFFF_FFFFFFFF and constants 0x8000<<13, 0x8000<<12,
// 4, 0xE, 0x50/0x51/0x52/0x53, ending with sync; return 6.
// Status: MISS - the middle block is bitfield-style read-modify-write, so it needs the
// original VU packet struct (bitfield layout) to be byte-exact. The 5 case groups, the
// guard and all eleven store offsets/constants are decoded above.
extern char D_0026BCC0[];
extern int FUN_00208450(void *fmt);

int FUN_001dcb68(char *p, short s1, short s2, short s3, short s4, short s5, short s6, short s7)
{
    int coeff = 0;

    switch (s3) {
    case 0:
        coeff = (s6 * s7) >> 2;
        break;
    case 1:
        coeff = (s6 * s7 * 3) >> 4;
        break;
    case 2:
    case 10:
        coeff = (s6 * s7) >> 3;
        break;
    case 19:
    case 27:
        coeff = (s6 * s7) >> 4;
        break;
    case 20:
    case 36:
        coeff = (s6 * s7) >> 5;
        break;
    }
    if (coeff > 0x7FFF) {
        FUN_00208450(D_0026BCC0);
        return 0;
    }
    return 6;
}
