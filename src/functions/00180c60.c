// FUNCTION: SLPM 0x00180C60  size 64  core 44
// q = *(int**)(p+0x44); if (FUN_0017f298(p) != 0) return 0;
// FUN_00180a68(q, q[3], 0, 0, 0); return 0;
extern int FUN_0017f298(char *);
extern void FUN_00180a68(int *, int, int, int, int);

int FUN_00180c60(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (FUN_0017f298(p) != 0)
        return 0;
    FUN_00180a68(q, q[3], 0, 0, 0);
    return 0;
}
