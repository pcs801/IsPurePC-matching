typedef unsigned long long u64;

extern unsigned int D_00249D4C;

int FUN_001dfd40(u64 *p, int variant)
{
    u64 a;
    u64 b;
    u64 c;
    u64 d;

    p[0] = 0x20000005ULL;
    p[1] = ((u64)(D_00249D4C | 5) << 32) | 0x4000ULL;
    p[2] = 0x1000000000008004ULL;
    p[3] = 0xEULL;
    if (variant == 0) {
        b = 0x42ULL;
        c = 0x49ULL;
        d = 0x3BULL;
        a = 0x4AULL;
    } else {
        b = 0x43ULL;
        c = 0x49ULL;
        d = 0x3BULL;
        a = 0x4BULL;
    }
    p[11] = a;
    p[5] = b;
    p[7] = c;
    p[9] = d;
    return 6;
}
