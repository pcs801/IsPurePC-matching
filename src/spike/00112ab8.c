// FUNCTION: SLPM 0x00112AB8  size 12
// sw $zero, 0xc($a0) ; jr $ra ; sw $zero, 8($a0)
void func_00112AB8(int *s) {
    s[2] = 0;
    s[3] = 0;
}
