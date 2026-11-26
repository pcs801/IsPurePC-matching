// FUNCTION: SLPM 0x00112BF8  size 32
// lw $v0,0xc($a0) ; blez ; nop ; lw $v0,0xc($a0) ; addiu -1 ; sw ; jr ; nop
void FUN_00112bf8(int *p) {
    if (p[3] > 0) {
        p[3] = p[3] - 1;
    }
}
