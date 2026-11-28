extern void FUN_001cf618(char *p);
extern char D_002664E0[];
extern int FUN_001b3c28(int a0);

int FUN_001b9558(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_002664E0);
        return -1;
    }
    return FUN_001b3c28(*(int *)(p + 4));
}
