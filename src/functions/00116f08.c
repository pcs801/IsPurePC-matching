// FUNCTION: SLPM 0x00116F08  size 88  core 88
extern char *D_00270CAC;
extern void FUN_00123568(void *a0);
extern void FUN_00128178(void *a0);
extern int FUN_0019d8d8(int a0);

int FUN_00116f08(int idx)
{
    int r;

    FUN_00123568(D_00270CAC + 0x3553C);
    FUN_00128178(D_00270CAC + 0x3B7D4);
    r = FUN_0019d8d8(*(int *)(D_00270CAC + idx * 4 + 1092));
    *(unsigned char *)(r + 13) = 0;
    return r;
}
