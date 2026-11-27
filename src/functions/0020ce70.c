// FUNCTION: SLPM 0x0020CE70  size 32  core 28
// jal FUN_0020bd60 with `addiu a1,zero,0x12` in the delay slot (a0 forwarded).
extern void FUN_0020bd60(int, int);

void FUN_0020ce70(int a0)
{
    do {
        FUN_0020bd60(a0, 0x12);
    } while (0);
}
