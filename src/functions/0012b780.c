// FUNCTION: SLPM 0x0012B780  size 40  core 36
// sig: sll ; lw ; addu ; sll ; addu ; lui ; addu ; jr ; sb ; nop

extern int D_00270CAC;

void FUN_0012b780(int a0, char a1)
{
    *(char *)(D_00270CAC + ((a0 << 5) + a0) * 8 + 0x3DEFC) = a1;
}
