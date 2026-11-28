extern void FUN_001cf618(char *p);
extern char D_00265AD8[];
extern int FUN_001c40c8(int a0);

int FUN_001b03a0(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00265AD8);
        return -1;
    }
    return FUN_001c40c8(*(int *)(p + 148));
}
