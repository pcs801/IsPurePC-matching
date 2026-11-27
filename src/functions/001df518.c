// FUNCTION: SLPM 0x001DF518  size 32 (core 28)
// Wrapper: a1 gets OR'd with 0x3000 in the jal delay slot. do/while(0) keeps the call a
// plain jal (ee-gcc would otherwise turn a single-call body into a sibling call).
extern void FUN_001df538(int a0, int a1);

void FUN_001df518(int a0, int a1)
{
    do {
        FUN_001df538(a0, a1 | 0x3000);
    } while (0);
}
