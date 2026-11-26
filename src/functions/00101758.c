// FUNCTION: SLPM 0x00101758  size 168  core 168
extern int D_01B7423C;
extern int FUN_001fc8c0();
extern int FUN_001ac8f8(int, void *, int, void *);
extern int FUN_001ad318(int);
extern int FUN_001b1af0(void);

int FUN_00101758(int idx, int a1, void *a2) {
    char *p = (char *)&D_01B7423C + ((idx << 6) + idx) * 8;
    char *q = p + 8;
    FUN_001fc8c0(q);
    FUN_001ac8f8(idx, q, 0, a2);
    while (FUN_001ad318(idx) != 3)
        FUN_001b1af0();
    *(int *)(p + 4) = idx;
    *(int *)p = 2;
    return 2;
}
