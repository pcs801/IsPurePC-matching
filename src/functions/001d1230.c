// FUNCTION: SLPM 0x001D1230  size 24
// ROM: ldl v0,7(a1) ; ldr v0,0(a1) ; sdl v0,0xA27(a0) ; jr ra ; sdr v0,0xA20(a0) ; nop
// Unaligned 8-byte copy: only a STRUCT assignment makes ee-gcc emit ldl/ldr + sdl/sdr
// (captain's t247 finding); *(unsigned long long*) would give aligned ld/sd.

struct S8 { char b[8]; };

void FUN_001d1230(char *dst, char *src)
{
    *(struct S8 *)(dst + 0xA20) = *(struct S8 *)src;
}
