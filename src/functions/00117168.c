// FUNCTION: SLPM 0x00117168  size 48 (core 44)
// note: the negation must be written as an early return (see 0x00117198 above):
//   if (FUN_001159f0(0) < D_B1EC08) return 0;  return 1;
// gives "slt v0,v0,a0 ; sltiu v0,v0,1" exactly; "return a >= b" / "!(a < b)" fold
// to xori and miss by one word.
extern int D_B1EC08;
extern int FUN_001159f0(int i);

int FUN_00117168(void)
{
    if (FUN_001159f0(0) < D_B1EC08)
        return 0;
    return 1;
}
