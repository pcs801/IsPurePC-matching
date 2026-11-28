// SLPM 0x001465A0 slice (core 44) holds TWO thunks, each a framed tail call:
//   0x001465A0 -> FUN_0010c230   0x001465B8 -> FUN_00145620
extern void FUN_0010c230(int, int, int, int);
extern void FUN_00145620(int, int, int, int);

void FUN_001465a0(int a, int b, int c, int d)
{
    FUN_0010c230(a, b, c, d);
}

void FUN_001465b8(int a, int b, int c, int d)
{
    FUN_00145620(a, b, c, d);
}
