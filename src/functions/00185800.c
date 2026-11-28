// FUNCTION: SLPM 0x00185800  size 64  core 44
// q = *(int**)(p+0x44); if (GATE(p) != 0) return 0; TARGET(q, 0x80 - q[3]); return 0;
extern int FUN_0017f298(char *);
extern void FUN_00184df8(int *, int);

int FUN_00185800(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (FUN_0017f298(p) != 0)
        return 0;
    FUN_00184df8(q, 0x80 - q[3]);
    return 0;
}
