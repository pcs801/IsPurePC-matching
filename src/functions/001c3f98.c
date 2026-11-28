extern char D_00268438[];
extern int FUN_001c4708(char *p);

int FUN_001c3f98(int a0, int a1)
{
    if (a0 == 0)
        return FUN_001c4708(D_00268438);
    if (a1 != 1)
        *(char *)(a0 + 4) = 0;
    else
        *(char *)(a0 + 4) = a1;
    return 0;
}
