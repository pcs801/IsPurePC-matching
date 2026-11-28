extern char D_00266CD8[];
extern int FUN_001bc358(char *p);
extern int FUN_0020a1c0(int a0, int a1, int a2);

int FUN_001bd270(int a0)
{
    if (a0 == 0) {
        FUN_001bc358(D_00266CD8);
        return -1;
    }
    if (*(int *)(*(int *)(a0) + 0x60) == 0)
        return 0;
    return FUN_0020a1c0(*(int *)(a0 + 4), 300, 0);
}
