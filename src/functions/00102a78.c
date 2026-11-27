// FUNCTION: SLPM 0x00102A78  size 144 (core 140)
extern char D_A94700[];
extern int FUN_001fbb84(void *p, int c, int n);

void FUN_00102a78(void)
{
    char *p = D_A94700 + 9;
    int i;

    D_A94700[0x46B8] = 0;
    FUN_001fbb84(D_A94700 + 0x46CC, 0, 0xC030);
    for (i = 0; i < 0x80; i++)
        p[0x46B0 + i / 8] &= ~(1 << (i % 8));
}
