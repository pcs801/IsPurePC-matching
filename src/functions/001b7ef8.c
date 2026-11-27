// FUNCTION: SLPM 0x001B7EF8  size 32  core 28
// jal FUN_001b3f30 with `lw a0,4(a0)` in the delay slot.
extern void FUN_001b3f30(int);

void FUN_001b7ef8(char *p)
{
    do {
        FUN_001b3f30(*(int *)(p + 4));
    } while (0);
}
