// FUNCTION: SLPM 0x00117198  size 48 (core 44)
// note: the negation must be written as an early return, not as a boolean operator.
//   if (FUN_001159f0(1) < D_B1EC0C) return 0;  return 1;
// makes ee-gcc emit "slt v0,v0,a0 ; sltiu v0,v0,1", while "return a >= b;" or
// "!(a < b)" both fold to "slt ; xori v0,v0,1" (1 word off).
extern int D_B1EC0C;
extern int FUN_001159f0(int i);

int FUN_00117198(void)
{
    if (FUN_001159f0(1) < D_B1EC0C)
        return 0;
    return 1;
}
