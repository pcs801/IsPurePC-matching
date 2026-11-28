// FUNCTION: SLPM 0x00208360  size 48  core 44
extern char D_0208268[];
extern void FUN_00207550(int, int *, int, int, int);

void FUN_00208360(int a0, int a1, int a2, int a3)
{
    int buf[1];

    buf[0] = a0;
    FUN_00207550((int)D_0208268, buf, a1, a2, a3);
}
