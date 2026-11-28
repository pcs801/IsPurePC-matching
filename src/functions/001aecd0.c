extern void FUN_001cf618(char *);
extern char D_002656C0[];

int FUN_001aecd0(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_002656C0);
        return -3;
    }
    return *(int *)(p + 0x10);
}
