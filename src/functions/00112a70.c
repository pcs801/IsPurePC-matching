// FUNCTION: SLPM 0x00112A70  size 72  core 68
// NEAR-MISS (2 words): store order. Target: p[3]=0, p[0]=a, p[2]=0, p[1]=q, blez, p[4]=n(delay).
// ee-gcc always emits the register store `sw a1,0(a0)` before the zero store `sw zero,0xC(a0)`;
// the other three stores, the blez and the delay-slot store match. The assignment order below
// (p[0] last) is the best of all 120 permutations (brute-forced) - only those two words differ.

void FUN_00112a70(int *p, int a, int *q, int n)
{
    p[3] = 0;
    p[2] = 0;
    p[1] = (int)q;
    p[4] = n;
    p[0] = a;
    if (n > 0) {
        do {
            *q = 0;
            q = (int *)((char *)q + 0x4CE40);
        } while (--n);
    }
}
