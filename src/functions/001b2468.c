unsigned int FUN_001b2468(char *p, int i)
{
    char *e = *(char **)(p + 0xC) + i * 4;
    int *q = *(int **)(e + 8);
    char *obj = *(char **)((char *)q + 8);
    unsigned int (*fn)(char *, int);

    fn = *(unsigned int (**)(char *, int))((char *)*(int **)obj + 0x24);
    return fn(obj, 0) >> 1;
}
