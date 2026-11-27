// FUNCTION: SLPM 0x001AB078  size 32 (core 28)
// Pure wrapper: the do/while(0) keeps ee-gcc from turning the call into a sibling call,
// so we get the target's jal + arg in the delay slot + framed epilogue.
extern void FUN_001aafe8(int, int, int, int, int);

void FUN_001ab078(int a0, int a1, int a2, int a3)
{
    do {
        FUN_001aafe8(a0, a1, a2, a3, 0x21);
    } while (0);
}
