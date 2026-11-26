// FUNCTION: SLPM 0x00155B68  size 12
// sw $a1,0x0($a0) ; jr $ra ; sw $zero,0x4($a0)
void FUN_00155b68(int *p, int v) {
    p[0] = v;
    p[1] = 0;
}