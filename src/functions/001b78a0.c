extern char D_00265F30[];
extern int FUN_001cf618(char *p);
extern int FUN_001b3dc8(int a0);

int FUN_001b78a0(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00265F30);
        return -1;
    }
    return (*(signed char *)(a0 + 1) < 2) ? 0 : FUN_001b3dc8(*(int *)(a0 + 4));
}
