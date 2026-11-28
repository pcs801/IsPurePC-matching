extern char D_00266110[];
extern int FUN_001cf618(char *p);

int FUN_001b7e90(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00266110);
        return 0;
    }
    return *(short *)(a0 + 0x40);
}
