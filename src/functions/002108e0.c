long long FUN_002108e0(int a0)
{
    int base = ((unsigned int)a0 >> 10) * 64;

    if (a0 < 0)
        return -1;
    if ((a0 & 0x3FF) != *(int *)(base + 8))
        return -1;
    if (*(int *)(base + 12) & 1)
        return *(long long *)(base + 16) - *(long long *)(base + 24);
    return 0;
}