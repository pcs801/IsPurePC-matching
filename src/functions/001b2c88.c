// FUNCTION: SLPM 0x001B2C88  size 48  core 60
// *(int*)(p+0x38) = a1; FUN_001cc520(*(int*)(p+4)); FUN_001cc338(*(int*)(p+4), a1);
// the field is re-read for the second call (the first call may clobber it).
extern void FUN_001cc520(int);
extern void FUN_001cc338(int, int);

void FUN_001b2c88(char *p, int a1)
{
    *(int *)(p + 0x38) = a1;
    FUN_001cc520(*(int *)(p + 4));
    FUN_001cc338(*(int *)(p + 4), a1);
}
