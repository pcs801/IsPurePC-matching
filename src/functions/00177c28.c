// FUNCTION: SLPM 0x00177C28  size 12
// sw $zero,0x16c($a0) ; jr $ra ; sw $zero,0x168($a0)
void FUN_00177c28(int *p) {
    p[0x168 / 4] = 0;
    p[0x16c / 4] = 0;
}
