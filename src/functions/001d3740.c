extern char D_0027A850[];
extern char D_0027A858[];
extern int FUN_001fb090(int a0, char *a1, int a2);

int FUN_001d3740(int a0)
{
    if (FUN_001fb090(a0, D_0027A850, 4) != 0)
        return 0;
    return FUN_001fb090(a0 + 8, D_0027A858, 4) == 0;
}
