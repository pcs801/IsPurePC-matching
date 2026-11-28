// FUNCTION: SLPM 0x00119878  size 64  core 60
// q = *(int**)(p+0x44); r = (int*)q[2];
// if (FUN_0012d980(*(unsigned char*)((char*)r+1), *(unsigned short*)((char*)r+2)) != 0) return;
// q = *(int**)(p+0x44); q[2] = q[2] + 4; FUN_00117dc0(p);
extern int FUN_0012d980(int, int);
extern void FUN_00117dc0(char *);

void FUN_00119878(char *p)
{
    int *q;
    int *r;

    q = *(int **)(p + 0x44);
    r = (int *)q[2];
    if (FUN_0012d980(*(unsigned char *)((char *)r + 1), *(unsigned short *)((char *)r + 2)) != 0)
        return;
    q = *(int **)(p + 0x44);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
}
