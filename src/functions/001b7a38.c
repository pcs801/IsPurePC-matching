// FUNCTION: SLPM 0x001B7A38  size 60  core 60
extern char D_00265FC0[];
extern void FUN_001cf618(void *a0);
extern int FUN_001b4050(int a0);

int FUN_001b7a38(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00265FC0);
        return -1;
    }
    if (*(signed char *)(p + 1) < 2)
        return FUN_001b4050(*(int *)(p + 4));
    return 0;
}
