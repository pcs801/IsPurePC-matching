void FUN_0019bc78(char *p, int a1, int a2, unsigned short a3)
{
    if (a1 < 0)
        return;
    if (!((unsigned int)a1 < *(unsigned int *)(p)))
        return;
    if (a2 < 0)
        return;
    if (!((unsigned int)a2 < *(unsigned int *)(p + 4)))
        return;
    *(unsigned short *)(*(int *)(p + 8) + (a1 + a2 * *(int *)(p)) * 2) = a3;
}