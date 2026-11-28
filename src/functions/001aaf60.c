extern int FUN_001a9ed0(int a0, int a1, char *a2, int a3, int a4);

int FUN_001aaf60(int a0, char *p)
{
    if (FUN_001a9ed0(a0, 31, p, 0, 4) >= 0)
        return *(int *)p;
    return -542;
}
