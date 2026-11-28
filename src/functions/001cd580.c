extern void FUN_001cff10(int a0, int a1, int a2, int a3, int a4);
extern void FUN_001cffa0(int a0);

void FUN_001cd580(char *p, int a1)
{
    int *q = (int *)(p + 0x48);
    int s0 = *(int *)(p + 8);
    int x = q[0];
    int y = q[5] + 2 * q[8];

    FUN_001cff10(s0, x, a1, y, 0);
    FUN_001cffa0(s0);
}
