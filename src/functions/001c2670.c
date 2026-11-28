extern char D_00268090[];
extern int FUN_001c1dc8(int a0, char *a1);

int FUN_001c2670(int a0)
{
    if (a0 == 0) {
        FUN_001c1dc8(0, D_00268090);
        return 0;
    }
    return *(int *)(a0 + 0x1C);
}
