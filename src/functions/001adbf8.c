extern char D_00265430[];
extern int FUN_001cf618(char *p);
extern int FUN_001b47e8(int a0);

int FUN_001adbf8(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00265430);
        return 0;
    }
    return FUN_001b47e8(*(int *)(a0 + 4));
}
