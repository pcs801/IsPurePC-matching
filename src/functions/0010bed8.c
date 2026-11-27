// FUNCTION: SLPM 0x0010BED8  size 72 (core 72)
// Empty VARIADIC function: the whole body is gcc's varargs register-save prologue
// (sd a1-a3/t0-t3 + swc1 f12-f19) followed by the epilogue. No va_start is needed,
// so it is expressible in plain C - just declare the ellipsis.
void FUN_0010bed8(int a, ...)
{
}
