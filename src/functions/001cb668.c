extern int D_00865BE0[];

void FUN_001cb668(int i)
{
    if (D_00865BE0[i * 2] != 0)
        ((void (*)(int))D_00865BE0[i * 2])(D_00865BE0[i * 2 + 1]);
}
