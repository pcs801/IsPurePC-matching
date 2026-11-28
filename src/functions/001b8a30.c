extern char D_00266328[];
extern int FUN_001cf618(char *p);

void FUN_001b8a30(int a0)
{
    if (a0 == 0) {
        FUN_001cf618(D_00266328);
        return;
    }
    *(short *)(a0 + 0x60) = 0;
    *(int *)(a0 + 0x64) = 0;
    *(short *)(a0 + 0x68) = 0;
    *(short *)(a0 + 0x6A) = 0;
}
