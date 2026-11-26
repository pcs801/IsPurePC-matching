// FUNCTION: SLPM 0x00105760  size 184 (core 184, includes the trailing 24-byte accessor at 0x00105800)
// note: bit set/clear shape as 0x00105698 on D_A98D50, then tail call FUN_00104c10();
//       the trailing 24 bytes are the word-table accessor at 0x00105800.
extern char D_A98D50[];
extern int *D_B2555C;
extern void FUN_00104c10(void);

void FUN_00105760(int p, int v)
{
    if (!v) {
        unsigned char *q = (unsigned char *)D_A98D50 + p / 8;
        *q &= ~(1 << (p - ((p / 8) << 3)));
    } else {
        unsigned char *q = (unsigned char *)D_A98D50 + p / 8;
        *q |= 1 << (p - ((p / 8) << 3));
    }
    FUN_00104c10();
}

int FUN_00105800(int p)
{
    return D_B2555C[p];
}
