// FUNCTION: SLPM 0x00105FB8  size 544
// sig: addiu ; sd ; sd ; sd ; sd ; sd ; sd ; daddu ; sd ; lui ; sll ; nop

extern char D_1B741B0[];
extern unsigned char D_00270C44[];
extern unsigned char D_00270C04[];
extern char D_0026FC28[];
extern char D_B264B0[];
extern int FUN_001e6120(int, int, int);
extern int FUN_001e6548(int, int, int, int);
extern int FUN_001e6680(int, int, int, int);
extern int FUN_001e6800(int, int, void *);
extern int FUN_001e6738(int, int, void *);
extern int FUN_001e60a8(int, int, void *);
extern void FUN_0019bde0(void);

void FUN_00105fb8(void)
{
    int i;
    int r;

    for (i = 0; i < 2; i++) {
        *(signed char *)(D_1B741B0 + i * 34) = -1;
        switch (FUN_001e6120(i, 0, -1)) {
        case 0:
            if (D_00270C44[i] == 0) {
                D_00270C44[i] = 3;
                FUN_001e60a8(i, 0, D_1B741B0 + i * 34);
            } else if (D_00270C44[i] == 3) {
                FUN_001e60a8(i, 0, D_1B741B0 + i * 34);
            }
            break;
        case 1:
            r = FUN_001e6548(i, 0, 2, 0);
            switch (D_00270C44[i]) {
            case 0:
                if (FUN_001e6680(i, 0, 1, 3) != 0)
                    D_00270C44[i] = 1;
                break;
            case 1:
                if (FUN_001e6800(i, 0, D_0026FC28) != 0) {
                    D_00270C04[i] = r;
                    D_00270C44[i] = 2;
                }
                break;
            case 2:
                D_00270C44[i] = 3;
                if (r != D_00270C04[i]) {
                    D_00270C44[i] = 1;
                } else {
                    FUN_001e6738(i, 0, D_B264B0 + i * 6);
                    FUN_001e60a8(i, 0, D_1B741B0 + i * 34);
                }
                break;
            case 3:
                if (r != D_00270C04[i]) {
                    D_00270C44[i] = 1;
                } else {
                    FUN_001e6738(i, 0, D_B264B0 + i * 6);
                    FUN_001e60a8(i, 0, D_1B741B0 + i * 34);
                }
                break;
            }
            break;
        }
    }
    FUN_0019bde0();
}
