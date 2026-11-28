extern char D_002653B8[];
extern void FUN_001cf618(char *p);
extern void FUN_001b4568(int a0, int a1, int a2, int a3, int a4);

int FUN_001ad968(char *p, int a1, int a2)
{
    if (a1 == 0) {
        FUN_001cf618(D_002653B8);
        return -1;
    }
    *(int *)(p + 0x30) = a2;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x0C) = 0x000FFFFF;
    FUN_001b4568(*(int *)(p + 4), a1, a2, 0, 0x000FFFFF);
    return 0;
}
