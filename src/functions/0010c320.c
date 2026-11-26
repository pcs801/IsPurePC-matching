// FUNCTION: SLPM 0x0010C320  size 1120
extern char D_B25800[];
extern char D_B25E80[];
extern char D_B25F60[];
extern char D_B260D0[];

extern void FUN_001dc520(void *p, int a, int b, int c, int d, int e, int f);
extern void FUN_001dbdd0(void *p, int a, int b, int c, int d, int e);
extern void FUN_001dc148(void *p, int a, int b, int c, int d, int e);
extern void FUN_001dc330(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void FUN_001dd920(void *p, int a, int b, int c, int d, int e, int f);
extern void FUN_001dd740(void *p, int a, int b, int c, int d, int e);
extern void FUN_001dc7b8(int a);
extern void FUN_001dc850(int a, int b);
extern void FUN_001ddc08(void *p, int a);
extern void FlushCache(int a);

typedef unsigned long long u64;

#define F(off) (*(u64 *)(D_B25800 + (off)))
#define G(off) (*(u64 *)(D_B25E80 + (off)))

void FUN_0010c320(void)
{
    FUN_001dc520(D_B25800, 0, 0x280, 0x1C0, 2, 0x32, 1);
    FUN_001dbdd0(D_B25800, 0, 0x280, 0x1C0, 0, 0);
    FUN_001dbdd0(D_B25800 + 0x28, 0, 0x280, 0x1C0, 0, 0);
    FUN_001dc148(D_B25800 + 0x60, 0, 0x280, 0x1C0, 2, 0x3A);
    FUN_001dc148(D_B25800 + 0x150, 0, 0x280, 0x1C0, 2, 0x3A);
    FUN_001dc330(D_B25800 + 0xE0, 2, 0x6C0, 0x720, 0x280, 0x1C0, 0x10, 0x60, 0x60, 0x80, 0);
    FUN_001dc330(D_B25800 + 0x1D0, 2, 0x6C0, 0x720, 0x280, 0x1C0, 0x10, 0x60, 0x60, 0x80, 0);
    F(0x60) = (F(0x60) & ~0x1FFULL) | 0x8C;
    F(0x38) = (F(0x38) & ~0x1FFULL) | 0x8C;
    F(0x70) = (F(0x70) & ~0x1FFULL) | 0x118;
    F(0x160) = (F(0x160) & ~0x1FFULL) | 0x118;
    F(0x150) = (F(0x150) & ~0x1FFULL) | 0x118;
    F(0x10) = (F(0x10) & ~0x1FFULL) | 0x8C;
    F(0x1F0) = 0x3F80000080000000ULL;
    F(0x100) = 0x3F80000080000000ULL;
    FUN_001dd920(D_B25E80, 0, 0x280, 0x1C0, 2, 0x32, 1);
    FUN_001dbdd0(D_B25E80, 0, 0x280, 0x1C0, 0, 0);
    FUN_001dbdd0(D_B25E80 + 0x28, 0, 0x280, 0x1C0, 0, 0);
    FUN_001dc148(D_B25E80 + 0x60, 0, 0x280, 0x1C0, 2, 0x3A);
    FUN_001dc148(D_B25E80 + 0x1D0, 0, 0x280, 0x1C0, 2, 0x3A);
    FUN_001dc330(D_B25E80 + 0x160, 2, 0x6C0, 0x720, 0x280, 0x1C0, 0x10, 0x60, 0x60, 0x80, 0);
    FUN_001dc330(D_B25E80 + 0x2D0, 2, 0x6C0, 0x720, 0x280, 0x1C0, 0x10, 0x60, 0x60, 0x80, 0);
    G(0x60) = (G(0x60) & ~0x1FFULL) | 0x8C;
    G(0x38) = (G(0x38) & ~0x1FFULL) | 0x8C;
    G(0x70) = (G(0x70) & ~0x1FFULL) | 0x118;
    G(0x1E0) = (G(0x1E0) & ~0x1FFULL) | 0x118;
    G(0xE0) = (G(0xE0) & ~0x1FFULL) | 0x8C;
    G(0xF0) = (G(0xF0) & ~0x1FFULL) | 0x118;
    G(0x260) = (G(0x260) & ~0x1FFULL) | 0x118;
    G(0x1D0) = (G(0x1D0) & ~0x1FFULL) | 0x8C;
    G(0x10) = (G(0x10) & ~0x1FFULL) | 0x8C;
    G(0x250) = (G(0x250) & ~0x1FFULL) | 0x118;
    FUN_001dd740(D_B25F60, 0, 0x280, 0x1C0, 0, 0x3A);
    FUN_001dd740(D_B260D0, 0, 0x280, 0x1C0, 0, 0x3A);
    *(u64 *)D_B25F60 = (*(u64 *)D_B25F60 & ~0x1FFULL) | 0x174;
    *(u64 *)D_B260D0 = (*(u64 *)D_B260D0 & ~0x1FFULL) | 0x174;
    G(0xF0) = (G(0xF0) & ~0x1FFULL) | 0x118;
    G(0x260) = (G(0x260) & ~0x1FFULL) | 0x118;
    G(0x2F0) = 0x3F80000080000000ULL;
    G(0x180) = 0x3F80000080000000ULL;
    FlushCache(0);
    FUN_001dc7b8(0);
    FUN_001ddc08(D_B25E80, 0);
    FUN_001dc850(0, 0);
    FUN_001ddc08(D_B25E80, 1);
    FUN_001dc850(0, 0);
}
