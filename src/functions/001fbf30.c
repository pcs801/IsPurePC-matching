// FUNCTION: SLPM 0x001FBF30  size 128  core 128
extern int FUN_001fbec0(void);

int FUN_001fbf30(char *p, unsigned int idx, int val)
{
    int *tbl;
    int r;

    if (idx >= 0x20) {
        *(int *)p = 0x16;
        return -1;
    }
    tbl = *(int **)(p + 0x1D4);
    if (tbl == 0) {
        if (FUN_001fbec0() != 0)
            return -1;
        tbl = *(int **)(p + 0x1D4);
    }
    r = tbl[idx];
    tbl[idx] = val;
    return r;
}
