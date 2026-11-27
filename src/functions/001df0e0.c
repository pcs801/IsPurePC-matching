// FUNCTION: SLPM 0x001DF0E0
int FUN_001df0e0(char *p)
{
    if (*(unsigned short *)(p + 0xE) == 0)
        return 0;
    return (int)(p + *(unsigned short *)(p + 0xC)) + *(int *)(p + 8);
}
