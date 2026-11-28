int FUN_00112b50(char *p)
{
    if (*(int *)(p + 0xC) == *(int *)(p + 0x10))
        return 0;
    return *(int *)p + *(int *)(p + 8) * 0x195000;
}
