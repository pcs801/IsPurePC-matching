extern void FUN_002059e0(int a0);
extern void FUN_002059c0(int a0);

int FUN_00114870(char *p)
{
    int v;

    FUN_002059e0(*(int *)(p + 64));
    v = (*(int *)(p + 16) << 11) + *(int *)(p + 20);
    FUN_002059c0(*(int *)(p + 64));
    return v;
}
