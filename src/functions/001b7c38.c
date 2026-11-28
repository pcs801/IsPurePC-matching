extern char D_00266050[];
extern int FUN_001cf618(char *p);

int FUN_001b7c38(int a0, int a1)
{
    if (a0 == 0) {
        FUN_001cf618(D_00266050);
        return 0;
    }
    return *(short *)(a0 + a1 * 2 + 0x42);
}
