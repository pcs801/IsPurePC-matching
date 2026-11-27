// FUNCTION: SLPM 0x001058F0  size 80  core 76
// T2 (change form): hold the loaded word in a 64-bit local so it cannot be coalesced with
// the absolute-address temporary -> address should stay in v1, value in v0.

extern unsigned char D_A969D0[];

void FUN_001058f0(int n, unsigned short idx, int val)
{
    int sum = idx;
    if (n > 0) {
        long long base = *(int *)0x00B1EC04;
        int *p = (int *)((char *)base + 0x10);
        do {
            sum += *p;
            p = (int *)((char *)p + 0x14);
        } while (--n);
    }
    D_A969D0[sum] = (unsigned char)(val + 1);
}
