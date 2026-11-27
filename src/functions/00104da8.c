// FUNCTION: SLPM 0x00104DA8  size 120  core 120  -G8
// MISS by exactly 2 words: ee-gcc materialises the stored constant 1 in $v0
// (addiu v0,zero,1 / sw v0,-0x6D78(gp)); the target uses $v1. Everything else -
// both memsets, the two 0x46Ax byte stores, the three calls and the gp-relative
// store order - is byte-exact, and the trailing "jr ra; nop" at 0x104E18 is the
// separate stub FUN_00104e18 kept in this file.
extern unsigned char D_A94700[];
extern int D_00270C38;
extern int D_00270C78;
extern int FUN_001fbb84(void *p, int c, int n);
extern void FUN_00102a78(void);
extern void FUN_00102190(void);
extern void FUN_0015a208(void);

void FUN_00104da8(void)
{
    unsigned char *base = D_A94700;

    FUN_001fbb84(base, 0, 0x108EC);
    FUN_001fbb84(base + 0x4450, 0xFF, 0x80);
    base[0x46AE] = 0;
    base[0x46B7] = 0;
    FUN_00102a78();
    FUN_00102190();
    FUN_0015a208();
    D_00270C38 = 0;
    D_00270C78 = 1;
}

void FUN_00104e18(void)
{
}
