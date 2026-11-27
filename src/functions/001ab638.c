// FUNCTION: SLPM 0x001AB638  size 32  core 28
// jal FUN_001ac5d0 with `addiu a0,zero,1` in the delay slot.
extern void FUN_001ac5d0(int);

void FUN_001ab638(void)
{
    do {
        FUN_001ac5d0(1);
    } while (0);
}
