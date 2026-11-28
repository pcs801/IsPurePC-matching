extern char D_00265F90[];
extern int FUN_001cf618(char *p);
extern int FUN_001b4048(int a0);

int FUN_001b79b0(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00265F90);
        return -1;
    }
    return (*(signed char *)(a0 + 1) < 2) ? 0 : FUN_001b4048(*(int *)(a0 + 4));
}
