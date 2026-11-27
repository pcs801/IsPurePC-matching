// FUNCTION: SLPM 0x00105FB8  size 544  core 540
extern char D_1B741B0[];
extern unsigned char D_00270C44;
extern unsigned char D_00270C04;
extern char D_0026FC28[];
extern char D_B264B0[];
extern int FUN_001e6120(int, int);
extern int FUN_001e6548(int, int, int, int);
extern int FUN_001e6680(int, int, int, int);
extern int FUN_001e6800(int, int, void *);
extern int FUN_001e6738(int, int, void *);
extern int FUN_001e60a8(int, int, void *);
extern void FUN_0019bde0(void);

void FUN_00105fb8(void)
{
    int i;
    int st;
    int r;
    char *base;
    char *slot;
    unsigned char *stp;

    for (i = 0; i < 2; i++) {
        base = D_1B741B0;
        slot = base + i * 34;
        stp = &(&D_00270C44)[i];
        *slot = -1;
        st = FUN_001e6120(i, 0);
        switch (st) {
        case 0:
        case 1:
        case 7:
            *stp = 0;
            break;
        case 2:
            if (*stp == 0) {
                *stp = 3;
                FUN_001e60a8(i, 0, slot);
            } else if (*stp == 3) {
                FUN_001e60a8(i, 0, slot);
            }
            break;
        case 6:
            r = FUN_001e6548(i, 0, 2, 0);
            switch (*stp) {
            case 0:
                if (FUN_001e6680(i, 0, 1, 3))
                    *stp = 1;
                break;
            case 1:
                if (FUN_001e6800(i, 0, D_0026FC28)) {
                    (&D_00270C04)[i] = r;
                    *stp = 2;
                }
                break;
            case 2:
                *stp = 3;
            case 3:
                if (r != (&D_00270C04)[i]) {
                    *stp = 1;
                } else {
                    FUN_001e6738(i, 0, (void *)(D_B264B0 + i * 6));
                    FUN_001e60a8(i, 0, slot);
                }
                break;
            }
            break;
        }
    }
    FUN_0019bde0();
}