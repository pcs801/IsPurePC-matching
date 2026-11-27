// FUNCTION: SLPM 0x0019A528  size 672
// Variadic text/control-string parser (see build/m26-tu/tu_0019a528/matched.md).
// Signature from the prologue: saves a2-a3, t0-t3 and f12-f19 into the stack varargs
// save area (frame 0x480 = 1024-byte buffer + 128-byte save area), sets a2 = &save_area,
// a0 = buf, calls 0x200E80 = vsprintf(buf, fmt, ap), then walks the produced text
// handling ESC (0x1B) sequences and the 16-bit codes 0x2440/0x2442/0x2443/0x2840/0x2842/
// 0x2843, calling 0x19BC00 / 0x19BBF0 / 0x19BD88 / 0x19B740, returning the counter s3.
// Status: MISS. Blockers: (a) ee-gcc's __builtin_va_start emits an unresolved relocation
// in this pipeline, and <stdarg.h> is banned, so the variadic prologue cannot be produced;
// (b) the ESC state machine (0x19A590-0x19A7A4) is not yet transcribed.
extern int FUN_00200e80(char *buf, const char *fmt, void *ap);

int FUN_0019a528(void *obj, const char *fmt, ...)
{
    char buf[1024];
    __builtin_va_list ap;

    __builtin_va_start(ap, fmt);
    FUN_00200e80(buf, fmt, ap);
    __builtin_va_end(ap);
    (void)obj;
    return 0;
}
