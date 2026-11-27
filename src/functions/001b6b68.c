// FUNCTION: SLPM 0x001B6B68  size 32  core 28
// jal FUN_001ce9b8 / jal FUN_001b6b90 / ld ra / j FUN_001ce9c0 (tail call)
extern void FUN_001ce9b8(void);
extern void FUN_001b6b90(void);
extern void FUN_001ce9c0(void);

void FUN_001b6b68(void)
{
    FUN_001ce9b8();
    FUN_001b6b90();
    FUN_001ce9c0();
}
