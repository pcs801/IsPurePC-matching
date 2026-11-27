// FUNCTION: SLPM 0x001B68E8  size 32  core 28
// lui v0,0x23 / lw v0,0x4c8(v0) / beqz -> skip / sd ra / jalr v0 / skip: ld ra / jr ra
extern void (*D_002304C8)(void);

void FUN_001b68e8(void)
{
    if (D_002304C8 != 0)
        D_002304C8();
}
