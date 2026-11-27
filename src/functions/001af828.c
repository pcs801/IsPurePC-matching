// FUNCTION: SLPM 0x001AF828  size 40 (core 36)
// Three-call thunk: the last call is the tail call (j FUN_001ce9c0).
extern void FUN_001ce9b8(void);
extern void FUN_001af850(void);
extern void FUN_001ce9c0(void);

void FUN_001af828(void)
{
    FUN_001ce9b8();
    FUN_001af850();
    FUN_001ce9c0();
}
