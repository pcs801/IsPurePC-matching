extern char D_002662F8[];
extern int FUN_001cf618(char *p);

int FUN_001b89d0(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_002662F8);
        return -1;
    }
    return *(short *)(a0 + 0x60);
}
