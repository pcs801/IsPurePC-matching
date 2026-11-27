// FUNCTION: SLPM 0x001AC710  size 48  core 48
// busy-wait delay: v0 = 0xC350; loop { v0-- } while (v0 != 0)
void FUN_001ac710(void)
{
    int i;

    for (i = 0xC350; i != 0; i--)
        ;
}
