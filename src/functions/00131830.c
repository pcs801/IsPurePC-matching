extern void FUN_001312b8(void);

int FUN_00131830(char *p)
{
    if (*(short *)(p + 0x10) == 0) {
        FUN_001312b8();
        *(short *)(p + 0x10) = 1;
    }
    return 0;
}
