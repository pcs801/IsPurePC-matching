extern char D_00266DB8[];
extern char D_00266DD8[];
extern int FUN_001bc358(char *p);

int FUN_001bd518(int a0)
{
    int v0;

    if (a0 == 0)
        return FUN_001bc358(D_00266DB8);
    v0 = *(int *)(*(int *)a0 + 0x34);
    if (v0 == 0)
        return FUN_001bc358(D_00266DD8);
    ((void (*)(int))v0)(*(int *)(a0 + 4));
    return 0;
}
