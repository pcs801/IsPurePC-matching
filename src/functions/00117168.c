// FUNCTION: SLPM 0x00117168  size 48 (core 44)
// MISS by one word: the negation of the comparison. Target emits
//   slt v0,v0,a0 ; sltiu v0,v0,1
// ee-gcc emits slt + xori v0,v0,1 instead (same semantics, different encoding).
// Tried: >=, !(a<b), (a<b)==0, (a<b)==0u, (unsigned)(a<b) < 1u, ternary ?0:1,
// boolean temp - every form folds to xori.
extern int D_B1EC08;
extern int FUN_001159f0(int i);

int FUN_00117168(void)
{
    return FUN_001159f0(0) >= D_B1EC08;
}
