extern char D_00265858[];
extern void FUN_001cf618(char *p);

void FUN_001af5f0(char *p, int v)
{
    if (*(signed char *)(p + 1) == 2) {
        FUN_001cf618(D_00265858);
        return;
    }
    *(int *)(p + 0x28) = v;
}
