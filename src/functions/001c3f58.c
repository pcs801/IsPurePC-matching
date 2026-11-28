// FUNCTION: SLPM 0x001C3F58  size 48  core 44
// FUN_001c46a0(a0, a1); SECOND(a0, a1); FUN_001c46a8();  (last call is the tail sibcall)
extern void FUN_001c46a0(char *, int);
extern void FUN_001c3f98(char *, int);
extern void FUN_001c46a8(void);

void FUN_001c3f58(char *a0, int a1)
{
    FUN_001c46a0(a0, a1);
    FUN_001c3f98(a0, a1);
    FUN_001c46a8();
}
