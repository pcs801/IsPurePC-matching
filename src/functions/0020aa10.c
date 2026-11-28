// FUNCTION: SLPM 0x0020AA10  size 48  core 52
// NEAR-MISS 4 words under -fno-schedule-insns/-insns2: only two instruction pairs are
// swapped (sd ra vs lui v0, and v0=0 vs ld ra). The array form is required: the target
// addresses the counter absolutely (lui v0,0x25 / sw zero,0x66d4(v0)) while a scalar
// declaration goes gp-relative under -G8.
extern char D_02566D4[];
extern char D_0870128[];
extern void FUN_001fbb84(char *, int, int);

int FUN_0020aa10(void)
{
    char *p;

    p = D_0870128;
    *(int *)D_02566D4 = 0;
    FUN_001fbb84(p, 0, 4);
    return 0;
}
