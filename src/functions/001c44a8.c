// FUNCTION: SLPM 0x001C44A8  size 48  core 44
// FUN_001c46a0(a0, a1); SECOND(a0, a1); FUN_001c46a8();  (last call is the tail sibcall)
extern void FUN_001c46a0(char *, int);
extern void FUN_001c44e8(char *, int);
extern void FUN_001c46a8(void);

void FUN_001c44a8(char *a0, int a1)
{
    FUN_001c46a0(a0, a1);
    FUN_001c44e8(a0, a1);
    FUN_001c46a8();
}
