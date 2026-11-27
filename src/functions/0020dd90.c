// FUNCTION: SLPM 0x0020DD90  size 32  core 28
// jal FUN_0020dd18 / nop / ld ra / jr ra
extern void FUN_0020dd18(void);

void FUN_0020dd90(void)
{
    do {
        FUN_0020dd18();
    } while (0);
}
