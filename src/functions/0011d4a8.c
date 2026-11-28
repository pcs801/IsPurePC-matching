// FUNCTION: SLPM 0x0011D4A8  size 80  core 80
extern int D_00270CAC;
extern void FUN_00117dc0(void *p);

int FUN_0011d4a8(char *p)
{
    int *q = *(int **)(p + 68);
    unsigned char *r = (unsigned char *)*(int *)((char *)q + 8);

    *(unsigned char *)((char *)D_00270CAC + 0x40000 - 0xB5A) = r[1];
    q = *(int **)(p + 68);
    q[2] = q[2] + 4;
    FUN_00117dc0(p);
    return 0;
}
