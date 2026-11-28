// FUNCTION: SLPM 0x001145F0  size 60  core 60
extern void FUN_002059e0(int a0);
extern void FUN_002059c0(int a0);

int FUN_001145f0(char *p)
{
    int r;

    FUN_002059e0(*(int *)(p + 64));
    r = *(int *)(p + 68);
    FUN_002059c0(*(int *)(p + 64));
    return r;
}
