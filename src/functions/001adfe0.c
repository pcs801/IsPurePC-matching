// FUNCTION: SLPM 0x001ADFE0  size 64  core 60
// r = MID(a0, a1) kept in a local; FIRST(a0,a1); LAST() has no arguments
extern void FUN_001af7d0(char *, int);
extern int FUN_001ae028(char *, int);
extern void FUN_001af7e8(void);

int FUN_001adfe0(char *a0, int a1)
{
    int r;

    FUN_001af7d0(a0, a1);
    r = FUN_001ae028(a0, a1);
    FUN_001af7e8();
    return r;
}
