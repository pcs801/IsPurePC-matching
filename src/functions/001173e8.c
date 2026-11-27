struct G {
    char pad0[0x68C4];
    int entries;
    unsigned int count;
    char pad1[0x6958 - 0x68CC];
    unsigned int count2;
};

// FUNCTION: SLPM 0x001173E8  size 208  core 204
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
    struct G *g;
    char *p;

    kept = 0;
    seen = 0;
    FUN_001053c0();
    g = (struct G *)D_B1EC00;
    p = (char *)g->entries;
    for (i = 0; i < g->count; i++) {
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
