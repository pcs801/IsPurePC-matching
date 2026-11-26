// FUNCTION: SLPM 0x00105D88  size 176  core 172
// MISS(25) candidate: prologue/epilogue/loop-control byte-exact; the map byte
// address (D_00A98D10 + i/8) is materialised as `lui at,%hi; addiu at,at,%lo;
// addu a0,at,q; lbu 0(a0)` in the target (reload-time $at split) but this
// ee-gcc only does that for CONST+REG; with a SYMBOL+REG it emits the folded
// `lui a0,%hi; addu a0,a0,q; lbu %lo(a0)` form twice (extra word).
struct BigState { char pad[0x6958]; unsigned int count; };
extern struct BigState D_00B1EC00;
extern unsigned char D_00A98D10[];
extern unsigned short FUN_00105818(int i);

void FUN_00105d88(int a) {
    int i;
    for (i = 0; i < D_00B1EC00.count; i++) {
        if (FUN_00105818(i) == a)
            ((unsigned char *)D_00A98D10)[i / 8] |= 1 << (i % 8);
    }
}
