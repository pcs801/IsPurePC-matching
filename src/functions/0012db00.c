// FUNCTION: SLPM 0x0012DB00  size 48  core 48
// sig: lw ; lui ; addu ; sb ; lw ; lui ; addu ; sb ; lui ; addu ; jr ; sh

extern int *D_00270CAC;

void FUN_0012db00(void) {
    unsigned char *p = (unsigned char *)D_00270CAC;
    unsigned char *q;

    p[0xD51F8] = 0;
    q = (unsigned char *)D_00270CAC;
    *(unsigned short *)(q + 0xD51FA) = 0;
    q[0xD51F9] = 0;
}
