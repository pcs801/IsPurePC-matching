extern char *D_00270BE0;
extern int FUN_00179188(int a0);
extern int FUN_00179158(int a0, int a1, int a2, int a3);
extern int FUN_00160770(void);
extern int FUN_0015d2d0(int a0, int a1);
extern int FUN_0015b898(int a0);
extern int FUN_001a08a8(int a0, int a1, int a2);
extern int FUN_00106668(int a0);
extern int FUN_0015b320(int a0, int a1);

#define G D_00270BE0
#define H h

int FUN_0015bd40(int a0, int a1)
{
    char *h;
    int s0;

    h = (char *)0xC56500;
    *(char *)(G + 0x5E) = 1;
    if (*(int *)(H + 0x10) & 0x10) {
        if (*(int *)(D_00270BE0 + 0x98) == 0 && (*(int *)(H + 8) & 0x10)) {
            FUN_00179188(1);
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
            return 0;
        }
        if (FUN_00179158(0, 1, 0, 0) == 0)
            FUN_0015b898(0);
        return 0;
    }
    if (*(int *)(H + 0x10) & 0x40) {
        if (*(int *)(G + 0x98) == *(int *)(G + 0xA4) - 1 && (*(int *)(H + 8) & 0x40)) {
            FUN_00179188(0);
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
            return 0;
        }
        if (FUN_00179158(1, 1, 0, 0) == 0)
            FUN_0015b898(1);
        return 0;
    }
    if (*(int *)(H + 0x10) & 0x80) {
        if (*(int *)(G + 0x98) == 0 && (*(int *)(H + 8) & 0x80)) {
            FUN_00179188(1);
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
            return 0;
        }
        if (FUN_00179158(0, 0, 0, 14) == 0) {
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
        }
        return 0;
    }
    if (*(int *)(H + 0x10) & 0x20) {
        if (*(int *)(G + 0x98) == *(int *)(G + 0xA4) - 1 && (*(int *)(H + 8) & 0x20)) {
            FUN_00179188(0);
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
            return 0;
        }
        if (FUN_00179158(1, 0, 0, 14) == 0) {
            *(int *)(G + 8) = *(int *)(G + 0x98);
            *(int *)(G + 0xC) = *(int *)(G + 0x9C);
            FUN_00160770();
            for (s0 = 0; s0 < *(int *)(G + 0xC4); s0++)
                FUN_0015d2d0(*(int *)(G + 0x14) + s0,
                             (*(int *)(G + 8) - *(int *)(G + 0xC) + s0) % 14);
        }
        return 0;
    }
    if (*(int *)(H + 8) & 0x800) {
        int t;

        t = *(int *)(G + 0x68);
        *(int *)(G + 0x68) = 1;
        if (t == 1) {
            if (*(int *)(G + 0x60) != 0) {
                *(int *)(G + 0x60) = 0;
            } else {
                *(int *)(G + 0x68) = 0;
                FUN_001a08a8(G + 0x70, 0, 0);
                *(int *)(G + 0x60) = 1;
            }
        }
    } else {
        FUN_001a08a8(G + 0x70, 250, 0);
        *(int *)(G + 0x60) = 0;
    }
    if (*(int *)(G + 0x00) != 1) {
        if (1 != 1) {
            ;
        }
    }
    if (*(int *)(H + 8) & 0x8000) {
        FUN_00106668(0);
        *(char *)(G + 0x5C) = (*(signed char *)(G + 0x5C) + 1) % 6;
        return 0;
    }
    if (*(int *)(H + 8) & 0x1000) {
        FUN_00106668(0);
        s0 = (*(int *)(G + 0x6C) + 1) % 5;
        if ((unsigned int)s0 < 5) {
            *(int *)(G + 0x6C) = s0;
            switch (s0) {
            case 0:
                FUN_0015b320(0, 0);
                break;
            case 1:
                FUN_0015b320(0, 0);
                break;
            case 2:
                FUN_0015b320(1, 1);
                break;
            case 3:
                FUN_0015b320(2, 0);
                break;
            case 4:
                FUN_0015b320(2, 1);
                break;
            }
        }
    }
    return 0;
}