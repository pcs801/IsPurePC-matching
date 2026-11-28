// FUNCTION: SLPM 0x00116eb0  size 88  core 84  -G8
extern char D_00213368[];
extern int D_00270CAC;
extern int FUN_0019daf8(int a0, int a1, int a2, int a3);

int FUN_00116eb0(int a0, int a1, int a2)
{
    int r = FUN_0019daf8((int)(D_00213368 + a0 * 12), a1, 0, a2);

    *(int *)(D_00270CAC + a0 * 4 + 0x444) = r;
    return r;
}
