// FUNCTION: SLPM 0x00185B60  size 48  core 44
// q = *(int**)(p+0x44); if (FUN_0017f298(p)) return 0; FUN_00185848(q, q[3]); return 0;
extern int FUN_0017f298(char *);
extern void FUN_00185848(int *, int);

int FUN_00185b60(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (FUN_0017f298(p) != 0)
        return 0;
    FUN_00185848(q, q[3]);
    return 0;
}
