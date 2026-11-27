// FUNCTION: SLPM 0x001174B8  size 120  core 120
// base = D_B1EC00 kept in a register, count at +0x6958.

extern char D_B1EC00[];
extern unsigned short FUN_00105818(int);
extern void FUN_00117638(int, int);

void FUN_001174b8(int mode)
{
    unsigned int i;
    char *base;

    base = D_B1EC00;
    for (i = 0; i < *(unsigned int *)(base + 0x6958); i++) {
        if (FUN_00105818(i) == mode)
            FUN_00117638(i, 1);
    }
}
