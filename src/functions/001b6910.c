// FUNCTION: SLPM 0x001B6910  size 32  core 28
// same shape with the callback pointer at 0x2304CC
extern void (*D_002304CC)(void);

void FUN_001b6910(void)
{
    if (D_002304CC != 0)
        D_002304CC();
}
