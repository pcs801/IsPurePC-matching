// FUNCTION: SLPM 0x001CC588  size 40 (core 36)
// Indirect call through the global function pointer at 0x00241E90.
extern void (*D_00241E90)(void);

void FUN_001cc588(void)
{
    D_00241E90();
}
