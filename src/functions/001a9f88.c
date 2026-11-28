// FUNCTION: SLPM 0x001a9f88  size 88  core 84
extern int FUN_001fbad4(int a0, int a1, int a2);

int FUN_001a9f88(char *p, int a1, int a2, int a3, int a4)
{
    int limit = *(int *)(p + 0x30) - (a2 << 2);

    if (a3 != 0) {
        if (a4 < 0 || limit < a4)
            return -0x21F;
        FUN_001fbad4((a2 << 2) + a1, a3, a4);
        return 0;
    }
    return 0;
}
