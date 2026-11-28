// FUNCTION: SLPM 0x0015a2f8  size 88  core 88  -G8
extern int D_00270BD8;
extern int D_00270C54;
extern int FUN_001598e0(void);
extern void FUN_0014ca40(void);

int FUN_0015a2f8(char *p)
{
    int r;

    D_00270BD8 = *(int *)(p + 0x44);
    r = FUN_001598e0();
    if (r != 2) {
        D_00270C54 = 3;
    } else {
        FUN_0014ca40();
        D_00270C54 = 1;
    }
    return r;
}
