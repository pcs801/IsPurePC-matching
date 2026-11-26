// FUNCTION: SLPM 0x0012D700  size 40  core 36
// sig: lw ; lui ; addu ; sb ; lw ; lui ; addu ; jr ; sh ; nop

extern int D_00270CAC;

void FUN_0012d700(unsigned char a0) {
    *(unsigned char *)((char *)D_00270CAC + 0x3F4A8) = a0;
    *(unsigned short *)((char *)D_00270CAC + 0x3F4AA) = 0;
}
