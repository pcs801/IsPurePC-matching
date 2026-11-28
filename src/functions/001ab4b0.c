// FUNCTION: SLPM 0x001AB4B0  size 56  core 56
extern char D_00861000[];
extern int FUN_001ab408(void);
extern int FUN_001fbb84(void *p, int c, int n);

int FUN_001ab4b0(void)
{
    int r = FUN_001ab408();

    FUN_001fbb84(D_00861000, 0, 784);
    return r;
}
