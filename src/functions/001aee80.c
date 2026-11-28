extern char D_00265748[];
extern void FUN_001cf618(char *p);
extern void FUN_001aeed8(void);
extern int FUN_001b5668(int a0);

int FUN_001aee80(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00265748);
        return -3;
    }
    FUN_001aeed8();
    return FUN_001b5668(*(int *)(p + 4));
}
