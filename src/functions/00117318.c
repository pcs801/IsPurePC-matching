extern int FUN_00115730(int a0);
extern int FUN_001173d0(int a0);
extern int FUN_001174b8(int a0);
extern char D_B1EC00[];

int FUN_00117318(void)
{
    char *base;
    char *p;
    unsigned int i;
    int done;
    int ok;

    base = D_B1EC00;
    done = 0;
    ok = 0;
    p = *(char **)(base + 0x68C4);
    for (i = 0; i < *(unsigned int *)(base + 0x68C8); i++) {
        if (FUN_00115730(*(short *)(p + 4)) != 0) {
            if (FUN_001173d0(*(unsigned short *)p) != 0)
                done++;
            ok++;
        }
        p += 0x10;
    }
    if (done < ok)
        return 0;
    FUN_001174b8(2);
    return 1;
}
