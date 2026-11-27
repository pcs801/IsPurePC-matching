// FUNCTION: SLPM 0x001DFD40  size 136 (core 132)  GIF fix-packet template, 35 callers
// Semantics per build/m26-semantics/001dfd40-skeleton.md:
//   p[0] = 0x20000005; p[2] = 0x1000000000008004; p[3] = 0xE;
//   p[1] = ((u64)(D_00249D4C | 5) << 32) | 0x4000;
//   p[11] = variant ? 0x4B : 0x4A;  p[5] = variant ? 0x43 : 0x42;
//   p[7] = 0x49; p[9] = 0x3B; return 6.  p[4]/0x30/0x40/0x50 are left untouched.
// Status: MISS 128/132. The if/else form is the only one that reproduces the target's
// opening "daddu t0,a0,zero" (the pointer is moved out of $a0, which is then used for
// the 0x1000000000008004 constant); the ternary form drops that move and shrinks the
// body to 120 bytes. Remaining 4-byte gap is sched2/register placement.
extern int D_00249D4C;

int FUN_001dfd40(unsigned long long *p, int variant)
{
    p[0] = 0x20000005ULL;
    p[2] = 0x1000000000008004ULL;
    p[3] = 0xEULL;
    p[1] = ((unsigned long long)(D_00249D4C | 5) << 32) | 0x4000ULL;
    if (variant) {
        p[11] = 0x4B;
        p[5] = 0x43;
    } else {
        p[11] = 0x4A;
        p[5] = 0x42;
    }
    p[7] = 0x49;
    p[9] = 0x3B;
    return 6;
}
