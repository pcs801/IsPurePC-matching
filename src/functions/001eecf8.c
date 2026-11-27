// FUNCTION: SLPM 0x001EECF8  size 16  core 16
// Target: move a1,a0 ; lui a0,0x27 ; j 0x208450 ; addiu a0,a0,-9232   (frameless tail call)
// Our best: the call shape matches but ee-gcc 2.96 wraps an external tail call in a
// 4-word frame (addiu sp,-16 / sd ra / ld ra / addiu sp,16) - a synthetic probe with
// "extern void H(int,int); void f(int x){ H(0x1234,x); }" reproduces that frame, so it is
// a compiler/codegen class, not a source-shape problem.
extern char D_0026DBF0[];
extern void FUN_00208450(void *fmt, int arg);

void FUN_001eecf8(int a)
{
    FUN_00208450(D_0026DBF0, a);
}
