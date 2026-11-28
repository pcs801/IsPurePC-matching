// FUNCTION: SLPM 0x00208580  size 72  core 72
// Region = three tiny leaf accessors at 0x00208580 / 0x00208598 / 0x002085B4.
extern char D_86D100[];
extern char D_86CF58[];

int FUN_00208580(int i)
{
    return *(int *)(D_86D100 + i * 4);
}

int FUN_00208598(int i, int v)
{
    *(int *)(D_86D100 + i * 4) = v;
    return v;
}

char *FUN_002085b4(void)
{
    return D_86CF58;
}
