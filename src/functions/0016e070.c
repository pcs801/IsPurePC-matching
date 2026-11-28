// FUNCTION: SLPM 0x0016E070  size 88  core 88
extern int D_00270590;
extern char D_00218DB8[];
extern void FUN_00169478(int a0, void *a1, int a2, int a3);

void FUN_0016e070(int a0)
{
    int i = D_00270590;
    int buf[4];

    FUN_00169478(a0, buf, *(int *)(D_00218DB8 + i * 16) + *(int *)(0x860000 + i * 36 - 0x1BE8) * 4, 0);
}
