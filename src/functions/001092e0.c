// FUNCTION: SLPM 0x001092E0  size 240
extern char D_0026FCF8[];
extern char D_00258570[];
extern char D_00258590[];
extern char D_1B741F8[];
extern int D_B257C8[];

extern void FUN_0020d2c0(void *p);
extern void FUN_0020d040(void *p, void *q, int a, int b, int c);
extern int FUN_0020ac78(void *p, int a, int b);
extern int FUN_0020b530(int fd, void *p, int n);
extern void FUN_0020af08(int fd);

int FUN_001092e0(void) {
    int fd;
    int i;

    FUN_0020d2c0(D_0026FCF8);
    FUN_0020d040(D_0026FCF8, D_00258570, 0, 0, 0);
    fd = FUN_0020ac78(D_00258590, 0x202, 0xFFFFF);
    if (fd < 0)
        return 1;
    for (i = 0; i < 9; i++) {
        FUN_0020b530(fd, &D_1B741F8[i], 1);
        FUN_0020b530(fd, &D_B257C8[i], 4);
    }
    FUN_0020af08(fd);
    FUN_0020d2c0(D_0026FCF8);
    return 0;
}
