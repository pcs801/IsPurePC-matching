// FUNCTION: SLPM 0x00184DB0  size 64  core 60
// q = *(int**)(p+0x44); if (FUN_0017f298(p) != 0) return 0;
// FUN_001843b0(q, 0x80 - q[3], 1, 1); return 0;
extern int FUN_0017f298(char *);
extern void FUN_001843b0(int *, int, int, int);

int FUN_00184db0(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (FUN_0017f298(p) != 0)
        return 0;
    FUN_001843b0(q, 0x80 - q[3], 1, 1);
    return 0;
}
