struct G {
    char pad0[0x68C4];
    int entries;
    unsigned int count;
    char pad1[0x6958 - 0x68CC];
    unsigned int count2;
};

// FUNCTION: SLPM 0x001174B8  size 120  core 120
extern char D_B1EC00[];
extern unsigned short FUN_00105818(int);
extern void FUN_00117638(int, int);

void FUN_001174b8(int mode)
{
    unsigned int i;

    for (i = 0; i < ((struct G *)D_B1EC00)->count2; i++) {
        if (FUN_00105818(i) == mode)
            FUN_00117638(i, 1);
    }
}
