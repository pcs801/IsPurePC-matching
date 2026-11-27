// FUNCTION: SLPM 0x0020E8A8  size 32  core 28
// jal FUN_0020e2b8 / nop / ld ra / jr ra (no argument setup at all)
extern void FUN_0020e2b8(void);

void FUN_0020e8a8(void)
{
    do {
        FUN_0020e2b8();
    } while (0);
}
