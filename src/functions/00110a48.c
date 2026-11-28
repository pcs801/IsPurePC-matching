extern void FUN_001e9090(int a0, int a1, int a2, int a3);

int FUN_00110a48(int a0)
{
    int i;

    for (i = 0; i < 2; i++) {
        FUN_001e9090(1, 0x8010, i | 0x980, a0);
        FUN_001e9090(1, 0x8010, i | 0xA80, a0);
    }
    return 0;
}
