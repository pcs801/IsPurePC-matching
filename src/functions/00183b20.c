// FUNCTION: SLPM 0x00183B20  size 64  core 44
// q = *(int**)(p+0x44); if (GATE(p) != 0) return 0; TARGET(q, 0x80 - q[3]); return 0;
extern int FUN_0017f6e8(char *);
extern void FUN_00183300(int *, int);

int FUN_00183b20(char *p)
{
    int *q;

    q = *(int **)(p + 0x44);
    if (FUN_0017f6e8(p) != 0)
        return 0;
    FUN_00183300(q, 0x80 - q[3]);
    return 0;
}
