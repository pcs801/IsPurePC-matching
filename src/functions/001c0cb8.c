extern char D_00267B88[];
extern int FUN_001c0340(int a0, char *a1);

int FUN_001c0cb8(int a0)
{
    if (a0 == 0) {
        FUN_001c0340(0, D_00267B88);
        return 0;
    }
    return *(signed char *)(a0 + 2);
}

int FUN_001c0cf0(void)
{
    return 2048;
}
