// FUNCTION: SLPM 0x0012D350  size 40  core 40
// sig: lw ; addiu ; lui ; addu ; lb ; slti ; slti ; xori ; jr ; movn

extern unsigned int D_00270CAC;

int FUN_0012d350(void)
{
    int x = ((signed char *)(D_00270CAC + 0x40000))[-0xCFC];
    int r = 1;
    if (x < 2) {
        r = 0;
        if (x < 0)
            r = 1;
    }
    return r;
}
