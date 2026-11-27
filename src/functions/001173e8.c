// FUNCTION: SLPM 0x001173E8  size 208  core 204
// base = D_B1EC00 kept in a register; entry table at +0x68C4, count at +0x68C8 (16-byte stride).

extern char D_B1EC00[];
extern void FUN_001053c0(void);
extern int FUN_00115730(int);
extern int FUN_001173d0(int);
extern int FUN_001174b8(int);

int FUN_001173e8(void)
{
    int kept;
    int seen;
    unsigned int i;
    char *base;
    char *p;

    kept = 0;
    seen = 0;
    FUN_001053c0();
    base = D_B1EC00;
    p = *(char **)(base + 0x68C4);
    for (i = 0; i < *(unsigned int *)(base + 0x68C8); i++) {
        if (FUN_00115730(*(short *)(p + 4)) != 0) {
            seen++;
            if (FUN_001173d0(*(unsigned short *)p) != 0)
                kept++;
        }
        p += 16;
    }
    if (kept < seen)
        return 1;
    return FUN_001174b8(2);
}
