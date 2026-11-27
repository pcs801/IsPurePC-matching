// FUNCTION: SLPM 0x00117920  size 88 (core 88)  -G8
extern unsigned char D_A94700[];
extern int D_00270CAC;
extern void FUN_00106668(int e);

void FUN_00117920(void)
{
    unsigned char v = D_A94700[0x46A2];
    unsigned char g = v & 1;

    if (g) {
        *(int *)(D_00270CAC + 0x48C) = 30;
        v = D_A94700[0x46A2];
    }
    g = (v >> 1) & 1;
    if (g)
        FUN_00106668(11);
}
