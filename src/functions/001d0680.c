// FUNCTION: SLPM 0x001D0680  size 96  core 88
// if (*(int*)(p+0xC) != 0) return 0; if (*(int*)(p+0x24) == 0) return 0; return 1;
int FUN_001d0680(char *p)
{
    if (*(int *)(p + 0xC) != 0)
        return 0;
    if (*(int *)(p + 0x24) == 0)
        return 0;
    return 1;
}
