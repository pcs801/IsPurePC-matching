// FUNCTION: SLPM 0x0020D2C0  size 32  core 28
// jal FUN_0020bd60 with `addiu a1,zero,0x15` in the delay slot (a0 forwarded).
extern void FUN_0020bd60(int, int);

void FUN_0020d2c0(int a0)
{
    do {
        FUN_0020bd60(a0, 0x15);
    } while (0);
}
