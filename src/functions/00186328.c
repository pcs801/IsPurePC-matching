// FUNCTION: SLPM 0x00186328  size 64  core 60
// FUN_0019b688(a0,a1); FUN_0019b710(a0,0,0); tail FUN_0019b888(a0, a1 & 0xFF);
extern void FUN_0019b688(char *, int);
extern void FUN_0019b710(char *, int, int);
extern void FUN_0019b888(char *, int);

void FUN_00186328(char *a0, int a1)
{
    FUN_0019b688(a0, a1);
    FUN_0019b710(a0, 0, 0);
    FUN_0019b888(a0, a1 & 0xFF);
}
