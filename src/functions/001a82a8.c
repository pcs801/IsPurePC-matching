// FUNCTION: SLPM 0x001A82A8  size 24
// lw $v0,0($a0) ; lw $v1,8($a0) ; sra $v0,$v0,0xc ; xor $v0,$v0,$v1 ; jr $ra ; sltiu $v0,$v0,1
int FUN_001a82a8(int *p) {
    return (p[0] >> 12) == p[2];
}
