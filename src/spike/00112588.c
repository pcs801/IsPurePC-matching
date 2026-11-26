// FUNCTION: SLPM 0x00112588  size 12
// addiu $v0, $zero, 1 ; jr $ra ; sw $v0, 0xa8($a0)
// void return: v0 is reused as a scratch register for the constant 1.
void func_00112588(int *s) {
    s[0x2a] = 1;
}
