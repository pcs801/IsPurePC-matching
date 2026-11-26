// FUNCTION: SLPM 0x0019B590  size 28
// lw $v0,0x24($a0) / lw $v1,0x28($a0) / sll x2 / sw 0x24 / jr / sw 0x28
void FUN_0019b590(int *p) {
    p[0x24 / 4] = p[0x24 / 4] * 2;
    p[0x28 / 4] = p[0x28 / 4] * 2;
}
