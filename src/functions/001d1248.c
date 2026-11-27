short FUN_001d1248(int self)
{
    if (*(signed char *)(self + 0x1A5) == 0)
        return 0;
    if (*(short *)(self + 0x200) == 0)
        return 0;
    return *(short *)(self + 0x202);
}
