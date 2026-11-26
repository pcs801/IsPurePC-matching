// FUNCTION: SLPM 0x001A8208  size 28
// sll $v0,$a1,0xc ; sw $a1,8($a0) ; sw $v0,4($a0) ; sw $a2,0x10($a0) ; sw $v0,0($a0) ; jr $ra ; sw $zero,0xc($a0)
// note: the five stores are independent; this statement order is the one that
// reproduces gcc 2.96's schedule (see docs/build.md, statement-order search).
void FUN_001a8208(int *p, int a, int b) {
    p[0] = a << 12;
    p[1] = a << 12;
    p[3] = 0;
    p[4] = b;
    p[2] = a;
}
