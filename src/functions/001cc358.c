extern void (*D_00241E7C)(void *p);

void FUN_001cc358(char *p)
{
    void *q = *(void **)(p + 0xC0);

    if (q != 0)
        D_00241E7C(q);
}
