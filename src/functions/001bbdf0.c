extern void FUN_001bbbc8(char *p);
extern void FUN_001d0298(int a0, int a1);
extern void FUN_001d0d78(int a0, int a1);

void FUN_001bbdf0(char *p)
{
    FUN_001bbbc8(p);
    FUN_001d0298(*(int *)(p + 4), *(int *)(p + 0x10));
    FUN_001d0d78(*(int *)(p + 0), *(int *)(p + 4));
    *(char *)(p + 9) = 1;
}
