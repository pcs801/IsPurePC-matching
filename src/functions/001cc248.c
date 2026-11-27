// FUNCTION: SLPM 0x001CC248  size 40 (core 40)
// If the state byte at +1 is 2, tail-call FUN_001cbfb8(p); otherwise fall to the epilogue.
extern void FUN_001cbfb8(void *p);

void FUN_001cc248(char *p)
{
    if (*(signed char *)(p + 1) == 2) {
        FUN_001cbfb8(p);
        return;
    }
}
