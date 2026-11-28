int FUN_001bd328(char *p)
{
    int (*fn)(int, int);

    if (p == 0)
        return 0;
    fn = *(int (**)(int, int))((char *)*(int **)p + 0x60);
    if (fn == 0)
        return 0;
    return fn(*(int *)(p + 4), 402);
}
