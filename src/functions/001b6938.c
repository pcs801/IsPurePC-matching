// FUNCTION: SLPM 0x001B6938  size 32  core 28
// same shape with the callback pointer at 0x2304D4
extern void (*D_002304D4)(void);

void FUN_001b6938(void)
{
    if (D_002304D4 != 0)
        D_002304D4();
}
