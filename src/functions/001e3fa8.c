// FUNCTION: SLPM 0x001E3FA8  size 24 (core 24)
// Stores a 16-byte value at *(int*)s, bumps the pointer and records it at +0xC.
// Status: 28/24, 5 words off - the target emits ONE 128-bit "sq", we emit two sd.
void FUN_001e3fa8(int *s, unsigned long long a, unsigned long long b)
{
    char *p = (char *)*s;

    *(unsigned long long *)p = a;
    *(unsigned long long *)(p + 8) = b;
    *s = (int)(p + 16);
    *(int *)((char *)s + 0xC) = (int)p;
}
