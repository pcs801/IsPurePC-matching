// FUNCTION: SLPM 0x0012D478  size 40  core 40
// sig: sll ; lw ; addu ; addiu ; sll ; addu ; lui ; addu ; jr ; sh

extern unsigned char *D_00270CAC;

void FUN_0012d478(int i) {
    *(short *)((char *)D_00270CAC + i * 12 + 0x40000 - 0xB80) = -1;
}
