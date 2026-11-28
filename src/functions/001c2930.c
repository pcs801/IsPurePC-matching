extern char D_00268090[];
extern int FUN_001c1dc8(int a0, char *a1);

int FUN_001c2930(int a0)
{
    if (a0 == 0) {
        FUN_001c1dc8(0, D_00268090);
        return 0;
    }
    return *(signed char *)(a0 + 2);
}

int FUN_001c2968(void)
{
    return 2048;
}
