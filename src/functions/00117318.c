extern int FUN_00115730(int a0);
extern int FUN_001173d0(int a0);
extern int FUN_001174b8(int a0);
extern char D_B1EC00[];

int FUN_00117318(void)
{
    char *p;
    int i;
    int n;
    int done;
    int ok;

    done = 0;
    ok = 0;
    n = *(int *)(D_B1EC00 + 0x68C8);
    if (n != 0) {
        p = *(char **)(D_B1EC00 + 0x68C4);
        for (i = 0; i < n; i++) {
            if (FUN_00115730(*(short *)(p + 4)) != 0) {
                FUN_001173d0(*(unsigned short *)p);
                ok++;
                if (FUN_001173d0(*(unsigned short *)p) != 0)
                    done++;
            }
            p += 0x10;
        }
    }
    if (done < ok)
        return 0;
    FUN_001174b8(2);
    return 1;
}
