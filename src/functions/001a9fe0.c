// FUNCTION: SLPM 0x001a9fe0  size 88  core 84
extern int FUN_001fbad4(int a0, int a1, int a2);

int FUN_001a9fe0(char *p, int a1, int a2, int a3, int a4)
{
    int off = a3 << 2;
    int limit = *(int *)(p + 0x30) - off;

    if (a1 != 0) {
        if (a4 < 0 || limit < a4)
            return -0x21F;
        FUN_001fbad4(a1, off + a2, a4);
        return 0;
    }
    return 0;
}
