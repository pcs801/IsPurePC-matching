// FUNCTION: SLPM 0x00002056C0  size 16  core 16
// Target is a pure libkernel syscall stub:
//   addiu $v1, $zero, 0x12
//   syscall
//   jr $ra
//   nop
// The syscall opcode (SPECIAL funct 0x0C) plus the syscall number in $v1 cannot be
// produced by plain C: ee-gcc 2.96 has no syscall builtin (__builtin_trap does not even
// compile here) and register choice is not expressible. Same known-hard class as
// src/functions/00100008.c. Minimal placeholder kept so the file exists and compiles.
void FUN_002056c0(void)
{
}
