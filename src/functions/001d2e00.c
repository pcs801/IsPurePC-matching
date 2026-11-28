// FUNCTION: SLPM 0x001D2E00  size 88  core 88
extern void FUN_001d2a88(void);
extern void FUN_001d2e60(void *p, int v, int w, int x);
extern void FUN_001d2aa0(void);

void FUN_001d2e00(char *p, short v, int w, int x)
{
    FUN_001d2a88();
    FUN_001d2e60(p, v, w, x);
    FUN_001d2aa0();
}
