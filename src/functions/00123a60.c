// FUNCTION: SLPM 0x00123A60  size 24  core 20
// sig: lw ; sw ; sw ; jr ; sw ; nop

extern int *D_00270CB0;

void FUN_00123a60(void) {
    int *p = D_00270CB0;
    p[0x1804] = 0;
    p[0x1805] = 0;
    p[0x1806] = 0;
}
