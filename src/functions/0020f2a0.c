// FUNCTION: SLPM 0x0020F2A0  size 48  core 44
extern int D_02566F8;
extern void FUN_0020f208(int *, int, int);

int FUN_0020f2a0(int idx)
{
    int buf;
    int n;

    n = 4;
    FUN_0020f208(&buf, D_02566F8 + idx * 4, n);
    return buf;
}
