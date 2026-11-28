extern int FUN_001b6520(int a0, char *a1, int a2);
extern void FUN_001c55f0(int a0, char *a1, int a2);

int FUN_001b6890(char *p, int b)
{
    int r = FUN_001b6520(2, p + 1024, b - 1024);

    if (r != 0)
        FUN_001c55f0(r, p, 1024);
    return r;
}
