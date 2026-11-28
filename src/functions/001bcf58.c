extern char D_00266B20[];
extern char D_00266B40[];
extern int FUN_001bc358(char *p);

int FUN_001bcf58(int a0)
{
    int v0;

    if (a0 == 0)
        return FUN_001bc358(D_00266B20);
    v0 = *(int *)(*(int *)a0 + 0x28);
    if (v0 == 0)
        return FUN_001bc358(D_00266B40);
    ((void (*)(int))v0)(*(int *)(a0 + 4));
    return 0;
}
