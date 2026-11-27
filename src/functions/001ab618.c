// FUNCTION: SLPM 0x001AB618  size 32 (core 28)
// Pure thunk; do/while(0) prevents the sibling call.
extern void FUN_001ac5d0(void);

void FUN_001ab618(void)
{
    do {
        FUN_001ac5d0();
    } while (0);
}
