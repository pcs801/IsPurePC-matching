// FUNCTION: SLPM 0x0012B1C8  size 56  core 56
// sig: slti ; sll ; addiu ; addu ; movz ; lw ; sll ; slti ; addu ; movn ; lui ; addu

extern int D_00270CAC;

void FUN_0012b1c8(int a0, int a1)
{
    if (a1 >= 10)
        a1 = 9;
    if (a1 < 0)
        a1 = 0;
    *(char *)(D_00270CAC + ((a0 << 5) + a0) * 8 + 0x3DEFD) = a1;
}
