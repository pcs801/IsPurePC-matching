extern char D_002660B0[];
extern int FUN_001cf618(char *p);

int FUN_001b7d78(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_002660B0);
        return 0;
    }
    return *(short *)(a0 + 0x46);
}
