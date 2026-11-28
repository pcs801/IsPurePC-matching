extern char D_00265F00[];
extern int FUN_001cf618(char *p);
extern int FUN_001b3e40(int a0);

int FUN_001b7818(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00265F00);
        return -1;
    }
    return (*(signed char *)(a0 + 1) < 2) ? 0 : FUN_001b3e40(*(int *)(a0 + 4));
}
