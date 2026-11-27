// FUNCTION: SLPM 0x00115F90  size 560  core 560
extern unsigned char *D_00270CAC;
extern unsigned char D_A94700[];
extern int FUN_00115b20(int, int);
extern int FUN_00115c28(int, int);
extern int FUN_00125a18(int, int);
extern void FUN_00106668(int);
extern void FUN_0011fcc8(void);
extern void FUN_00125a58(int);

void FUN_00115f90(unsigned int a0)
{
    unsigned short s0;
    unsigned char m;
    unsigned char f;

    if (a0 == 0xFFFF)
        return;
    s0 = (unsigned short)(a0 & 0xFFFF);
    D_00270CAC[0x47A] = (unsigned char)FUN_00115b20(*(int *)(D_00270CAC + 0x52E0), s0);
    FUN_00115c28(*(int *)(D_00270CAC + 0x52E0), s0);
    if (D_00270CAC[0x47A] != 0)
        FUN_00125a18(0, 0);
    else if (FUN_00125a18(0, 1) != 0)
        FUN_00106668(4);
    if (D_00270CAC[0x47A] != 0) {
        if (D_00270CAC[0x47D] == 2) {
            D_00270CAC[0x47D] = 1;
            FUN_00125a18(1, 0);
            FUN_00125a18(1, 1);
        }
        return;
    }
    if (D_A94700[0x46A0] != 0)
        return;
    m = D_00270CAC[0x47D];
    if (m == 1) {
        f = D_A94700[0x46A2];
        if (f & 1) {
            *(int *)(D_00270CAC + 0x48C) = 30;
            f = D_A94700[0x46A2];
        }
        if ((f >> 1) & 1)
            FUN_00106668(11);
    }
    if (D_00270CAC[0x47D] == 1)
        FUN_0011fcc8();
    D_00270CAC[0x47C] = 0;
    D_00270CAC[0x47D] = 0;
    D_00270CAC[0x47E] = 0;
    D_00270CAC[0x47F] = 0;
    D_00270CAC[0x480] = 0;
    FUN_00125a18(1, 0);
    if (m == 1) {
        if (D_A94700[0x46A1] == 0) {
            D_00270CAC[0x47B] = m;
            D_00270CAC[0x47D] = 2;
            FUN_00125a18(1, 1);
            FUN_00125a18(2, 1);
        } else if (D_A94700[0x46A1] == 1) {
            D_00270CAC[0x47D] = 2;
            FUN_00125a18(1, 1);
        }
    } else if (m == 2) {
        FUN_00125a18(1, 1);
        FUN_00125a58(1);
        D_00270CAC[0x47D] = m;
    }
}
