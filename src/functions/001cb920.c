// FUNCTION: SLPM 0x001cb920  size 64  core 64 (two functions in one symbol)
// wrapper + 7-entry table getter; table base 0x00241AB0 has no symbol entry.
extern void FUN_001cb718(int a0);

void FUN_001cb920(void)
{
    FUN_001cb718(7);
}

int FUN_001cb938(unsigned int i)
{
    int *t = (int *)0x00241AB0;

    if (i < 7)
        return t[i];
    return 0;
}
